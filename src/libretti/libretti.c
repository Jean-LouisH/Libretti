#include "include/libretti.h"

#include <math.h>
#include "include/script_validator.h"
#include "include/validation.h"
#include "include/compiler.h"
#include "include/file.h"
#include "include/waveform_generator.h"

#include <stdlib.h>
#include <stdio.h>

static int g_libretti_id_count = -1;

lb_Libretti* lb_create_libretti(const char* filename)
{
	lb_Libretti* libretti = malloc(sizeof *libretti);
	if (libretti != 0)
	{
		libretti->composition = lb_create_composition(filename);
		libretti->playback = lb_create_playback();
		if (g_libretti_id_count != -1)
		{
			libretti->id = g_libretti_id_count;
			g_libretti_id_count++;
		}
	}
	return libretti;
}

lb_Libretti* lb_create_empty_libretti()
{
	lb_Libretti* libretti = malloc(sizeof *libretti);
	if (libretti != 0)
	{
		libretti->composition = lb_create_empty_composition();
		libretti->playback = lb_create_playback();
		if (g_libretti_id_count != -1)
		{
			libretti->id = g_libretti_id_count;
			g_libretti_id_count++;
		}
	}
	return libretti;
}

lb_Composition* lb_create_composition(const char* filename)
{
	lb_Composition* composition = lb_create_empty_composition();
	if (composition != 0)
		lb_compile_composition_from_script_file(composition, filename);
	return composition;
}

lb_Composition* lb_create_empty_composition()
{
	lb_Composition* composition = calloc(1, sizeof(lb_Composition));
	if (composition != 0)
		composition->validation_statuses = LB_VALIDATION_SCRIPT_FILE_NOT_LOADED;
	return composition;
}

lb_Playback* lb_create_playback()
{
	return calloc(1, sizeof(lb_Playback));
}

int lb_validate_script_file(const char* filename)
{
	char* script = load_ascii_string_from_file(filename).data;
	int validation_statuses = validate_script(script);
	free(script);
	return validation_statuses;
}

void lb_compile_composition_from_script_file(lb_Composition* composition, const char* filename)
{
	char* script = load_ascii_string_from_file(filename).data;
	if (script != 0)
	{
		compile_composition_from_script(composition, script);
		free(script);
	}
	else
	{
		composition->validation_statuses = LB_VALIDATION_SCRIPT_FILE_NOT_LOADED;
		printf("\n\n_error 0x%X: \tLB_VALIDATION_SCRIPT_FILE_NOT_LOADED -> The file '%s' may be missing.\n",
			LB_VALIDATION_SCRIPT_FILE_NOT_LOADED,
			filename);
	}
}

void lb_update_playback(lb_Playback* playback, lb_Composition* composition)
{
	lb_Note* current_notes = malloc(composition->track_count * (sizeof * current_notes));
	lb_update_notes_from_composition(current_notes, composition, playback);
	playback->current_waveforms.count = composition->track_count;
	lb_update_waveform_from_notes(&playback->current_waveforms, current_notes, composition->track_count);

	for (int i = 0; i < LYRICS_LENGTH; i++)
		playback->current_lyrics[i] = '\0';

	/* Find the current lyrics. */
	for (int i = 0; i < composition->lyrics_event_count; i++)
		if (playback->current_play_time > composition->lyrics_events[i].start_time)
			for (int j = 0; j < LYRICS_LENGTH; j++)
				playback->current_lyrics[j] = composition->lyrics_events[i].lyrics[j];

	free(current_notes);
}

void lb_update_notes_from_composition(lb_Note current_notes[], lb_Composition* composition, lb_Playback* playback)
{
	for (int i = 0; i < composition->track_count; i++)
	{
		/*Prevents note searches on lyrics audio scopes*/
		if (composition->tracks[i].note_count > 0)
		{
			lb_NoteEvent note_event = composition->tracks[i].note_events[playback->track_note_indices[i]];
			lb_Note silent_note = { 0 };
			lb_NoteEvent next_note_event;

			if (playback->track_note_indices[i] < composition->tracks[i].note_count - 1)
			{
				next_note_event = composition->tracks[i].note_events[playback->track_note_indices[i] + 1];
			}
			else
			{
				next_note_event.note = silent_note;
				next_note_event.start_time = composition->time_length;
			}

			/*Find and set the current note to play*/
			while ((playback->current_play_time > next_note_event.start_time))
			{
				if (playback->track_note_indices[i] < composition->tracks[i].note_count - 1)
				{
					playback->track_note_indices[i]++;
					note_event = composition->tracks[i].note_events[playback->track_note_indices[i]];
					next_note_event = composition->tracks[i].note_events[playback->track_note_indices[i] + 1];
				}
				else
				{
					next_note_event.note = silent_note;
					next_note_event.start_time = composition->time_length;
				}

				/*Reset the song when the time exceeds the last time stamp.*/
				if (playback->current_play_time > composition->time_length)
				{
					playback->play_states |= LB_PLAYBACK_STATE_PLAYED_AT_LEAST_ONCE;
					playback->current_loop_count++;

					if ((playback->current_loop_count < composition->loop_count) ||
						composition->loop_count == pow(2, (sizeof composition->loop_count) * 8) - 1)
					{
						playback->current_play_time = composition->loop_timestamp;

						for (int j = 0; j < composition->track_count; j++)
						{
							playback->track_note_indices[j] = 0;

							/*Find and set note indices to loop time stamps.*/
							while (composition->loop_timestamp >
								composition->tracks[j].note_events[playback->track_note_indices[j]].start_time)
							{
								playback->track_note_indices[j]++;
							}
						}
					}
					else
					{
						playback->play_states &= ~LB_PLAYBACK_STATE_IS_PLAYING;
					}
				}	
			}

			const float slur_time_ratio = 1.0;
			const float normal_time_ratio = 0.85;
			const float staccato_time_ratio = 0.15;

			float current_time_ratio = normal_time_ratio;

			switch (note_event.note.articulation)
			{
				case LB_ARTICULATION_SLUR: current_time_ratio = slur_time_ratio; break;
				case LB_ARTICULATION_NORMAL: current_time_ratio = normal_time_ratio; break;
				case LB_ARTICULATION_STACCATO: current_time_ratio = staccato_time_ratio; break;
			}

			float note_lift_time = (note_event.start_time +
				((next_note_event.start_time - note_event.start_time) * current_time_ratio));

			if (playback->current_play_time > note_lift_time)
			{
				current_notes[i] = silent_note;
			}
			else
			{
				current_notes[i] = composition->tracks[i].note_events[playback->track_note_indices[i]].note;
			}
		}
	}
}

void lb_update_waveform_from_notes(lb_Waveforms* waveforms, lb_Note current_notes[], uint8_t track_count)
{
	generate_waveform(waveforms, current_notes);
}

void lb_increment_play_time(lb_Libretti* libretti, float delta_time)
{
	if (libretti->playback->play_states & LB_PLAYBACK_STATE_IS_PLAYING)
		libretti->playback->current_play_time += delta_time;
}

void lb_load(lb_Libretti* libretti, const char* filename)
{
	lb_compile_composition_from_script_file(libretti->composition, filename);
	lb_play(libretti);
}

void lb_play(lb_Libretti* libretti)
{
	libretti->playback->play_states |= LB_PLAYBACK_STATE_IS_PLAYING;
}

void lb_pause(lb_Libretti* libretti)
{
	libretti->playback->play_states &= ~LB_PLAYBACK_STATE_IS_PLAYING;
}

void lb_reset(lb_Libretti* libretti)
{
	libretti->playback->current_play_time = 0.0;
	for (int i = 0; i < MAX_TRACKS; i++)
		libretti->playback->track_note_indices[i] = 0;
}

void lb_stop(lb_Libretti* libretti)
{
	lb_reset(libretti);
	lb_pause(libretti);
}

void lb_save_binary_u8_to_file(lb_BinaryU8* binary, const char* filename)
{
	save_binary_u8_to_file(binary, (char*)filename);
}

void lb_save_binary_s16_to_file(lb_BinaryS16* binary, const char* filename)
{
	save_binary_s16_to_file(binary, (char*)filename);
}

void lb_append_binary_u8_to_file(lb_BinaryU8* binary, const char* filename)
{
	append_binary_u8_to_file(binary, (char*)filename);
}

void lb_append_binary_s16_to_file(lb_BinaryS16* binary, const char* filename)
{
	append_binary_s16_to_file(binary, (char*)filename);
}

lb_BinaryS16 lb_get_spectrum_data(lb_Composition* composition)
{
	lb_Playback* playback = lb_create_playback();
	lb_BinaryS16 spectrum;

	int max_note_count = 0;

	/* For now, with only single track support,
	 * get the longest track, which is likely where the 
	 * melody is located. */
	for (int i = 0; i < composition->track_count; i++)
		if (composition->tracks[i].note_count > max_note_count)
			max_note_count = composition->tracks[i].note_count;

	int stream_length = max_note_count * SAMPLE_SIZE;
	spectrum.data = calloc(stream_length, sizeof(int16_t));

	/*Building the export binary stream*/
	while (!(playback->play_states & LB_PLAYBACK_STATE_PLAYED_AT_LEAST_ONCE))
	{
		int stream_position = 0;
		lb_update_playback(playback, composition);
		for (int i = 0; i < SAMPLE_SIZE; i++)
		{
			spectrum.data[stream_position] += playback->current_waveforms.streams[0][i];
			stream_position++;
		}
		playback->current_play_time += 17.0 / 1000.0;
	}

	return spectrum;
}

void lb_free_playback(lb_Playback* playback)
{
	free(playback);
	playback = 0;
}

void lb_free_composition(lb_Composition* composition)
{
	if (composition->tracks->note_events != 0)
		free(composition->tracks->note_events);
	if (composition->tempo_events != 0)
		free(composition->tempo_events);
	if (composition->lyrics_events != 0)
		free(composition->lyrics_events);
	free(composition);
	composition = 0;
}

void lb_free_libretti(lb_Libretti* libretti)
{
	lb_free_playback(libretti->playback);
	lb_free_composition(libretti->composition);
	libretti->playback = 0;
	libretti->composition = 0;
	free(libretti);
	libretti = 0;
}