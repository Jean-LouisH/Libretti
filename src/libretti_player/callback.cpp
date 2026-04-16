#include "callback.hpp" 
#include "callback_list.hpp"
#include "constants.h"
#include <file.h>
#include <mixer.h>
#include <SDL.h>

static CallbackList* g_callback_list = 0;

void initialize_callback()
{
	if (g_callback_list == 0)
	{
		g_callback_list = (CallbackList*)calloc(1, sizeof(CallbackList));
		if (g_callback_list != 0)
		{
			g_callback_list->capacity = 2;
			g_callback_list->libretti_list = (lb_Libretti**)calloc(g_callback_list->capacity, sizeof(lb_Libretti*));
			initialize_audio_playback(g_callback_list);
		}
	}
}

void add_libretti_to_callback(lb_Libretti* libretti)
{
	if (g_callback_list != 0)
	{
		libretti->playback->audio_device_id = g_callback_list->audio_device_id;
		libretti->playback->play_states = 0;
		libretti->playback->current_loop_count = 0;
		libretti->playback->output_volume = 1.0;
		lb_reset(libretti);
		lb_play(libretti);

		/* Expand the CallbackList when it gets full.*/
		if (g_callback_list->size == g_callback_list->capacity - 1)
		{
			int new_capacity = g_callback_list->capacity * 2;
			g_callback_list->libretti_list = (lb_Libretti**)realloc(g_callback_list->libretti_list, new_capacity * sizeof(lb_Libretti*));
			if (g_callback_list->libretti_list != 0)
				g_callback_list->capacity = new_capacity;
		}

		/* If the capacity expansion were successful, add the Libretti
		 * to the end of the list.*/
		if (g_callback_list->size < g_callback_list->capacity - 1)
		{
			g_callback_list->libretti_list[g_callback_list->size] = libretti;
			g_callback_list->size++;
		}
	}
}

void remove_libretti_from_callback(int libretti_id)
{
	if (g_callback_list != 0)
	{
		if (g_callback_list->libretti_list != 0)
		{
			/*Simple linear search implementation since they're not intended
			 * to be much larger than 10 at a time.*/
			for (int i = 0; i < g_callback_list->size; i++)
			{
				if (g_callback_list->libretti_list[i]->id == libretti_id)
				{
					/* If it's not the last entry, swap and shuffle all the later entries
					 * to the front of the list.*/
					for (int j = i; j < g_callback_list->size - 1; j++)
					{
						g_callback_list->libretti_list[j] = g_callback_list->libretti_list[j + 1];
					}

					g_callback_list->libretti_list[g_callback_list->size - 1] = 0;
					g_callback_list->size--;
					break;
				}
			}
		}
	}
}

lb_Libretti* create_and_add_libretti_to_callback(const char* filename)
{
	lb_Libretti* libretti = lb_create_libretti(filename);
	if (libretti != 0)
		add_libretti_to_callback(libretti);
	return libretti;
}

lb_Libretti* create_and_add_empty_libretti_to_callback()
{
	lb_Libretti* libretti = lb_create_empty_libretti();
	if (libretti != 0)
		add_libretti_to_callback(libretti);
	return libretti;
}

void increment_all_play_times(float delta_time)
{
	if (g_callback_list != 0)
	{
		for (int i = 0; i < g_callback_list->size; i++)
		{
			lb_Libretti* libretti = g_callback_list->libretti_list[i];
			lb_increment_play_time(libretti, delta_time);
		}
	}
}

lb_Libretti* play_note_for(
	uint16_t key,
	uint16_t dynamic,
	uint8_t panning,
	uint8_t timbre,
	uint8_t articulation,
	float duration)
{
	lb_Libretti* libretti = lb_create_empty_libretti();
	lb_Composition* composition = libretti->composition;
	composition->track_count = 1;
	composition->tracks[0].note_events = (lb_NoteEvent*)calloc(1, sizeof(lb_NoteEvent));

	if (composition->tracks[0].note_events != 0)
	{
		composition->tracks[0].note_count = 1;
		composition->tracks[0].note_events->start_time = 0.0;
		composition->tracks[0].note_events->note.dynamic = dynamic;
		composition->tracks[0].note_events->note.articulation = articulation;
		composition->tracks[0].note_events->note.key = key;
		composition->tracks[0].note_events->note.panning = panning;
		composition->tracks[0].note_events->note.timbre = timbre;
		composition->key_signature = LB_KEY_SIGNATURE_C_MAJOR;
		composition->loop_count = 0;
		composition->loop_timestamp = 0.0;
		composition->lyrics_event_count = 0;
		composition->tempo_event_count = 0;
		composition->time_length = duration;
		composition->time_signature[0] = 4;
		composition->time_signature[1] = 4;
		add_libretti_to_callback(libretti);
	}

	return libretti;
}

lb_Libretti* play_note(
	uint16_t key,
	uint16_t dynamic,
	uint8_t panning,
	uint8_t timbre)
{
	return play_note_for(
		key,
		dynamic,
		panning,
		timbre,
		LB_ARTICULATION_NORMAL,
		INFINITY);
}

lb_Libretti* play_simple_note_for(
	uint16_t key,
	uint16_t dynamic,
	float duration)
{
	return play_note_for(
		key,
		dynamic,
		LB_PANNING_CENTRE,
		LB_TIMBRE_SQUARE_WAVE,
		LB_ARTICULATION_NORMAL,
		duration);
}

lb_Libretti* play_simple_note(
	uint16_t key,
	uint16_t dynamic)
{
	return play_simple_note_for(
		key,
		dynamic,
		INFINITY);
}

void play_all()
{
	for (int i = 0; i < g_callback_list->size; i++)
		lb_play(g_callback_list->libretti_list[i]);
}

void pause_all()
{
	for (int i = 0; i < g_callback_list->size; i++)
		lb_pause(g_callback_list->libretti_list[i]);
}

void reset_all()
{
	for (int i = 0; i < g_callback_list->size; i++)
		lb_reset(g_callback_list->libretti_list[i]);
}

void stop_all()
{
	for (int i = 0; i < g_callback_list->size; i++)
		lb_stop(g_callback_list->libretti_list[i]);
}

lb_BinaryS16* get_audio_capture_stream_buffer()
{
	lb_BinaryS16* binary = (lb_BinaryS16*)calloc(1, sizeof *binary);
	if (binary != 0)
	{
		binary->size = DEFAULT_STREAM_SAMPLE_SIZE;
		binary->data = (int16_t*)calloc(DEFAULT_STREAM_SAMPLE_SIZE, sizeof * binary->data);
		initialize_audio_capture(binary);
	}
	return binary;
}

void initialize_audio_playback(CallbackList callback_list[])
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
	}
	else
	{
		SDL_AudioSpec desired;
		SDL_AudioSpec obtained;

		SDL_memset(&desired, 0, sizeof(desired));
		desired.freq = DEFAULT_STREAM_SAMPLE_FREQUENCY;
		desired.format = AUDIO_S16SYS;
		desired.channels = DEFAULT_STREAM_CHANNEL_COUNT;
		desired.samples = DEFAULT_STREAM_SAMPLE_SIZE;
		desired.callback = (SDL_AudioCallback)run_callback_play;
		desired.userdata = callback_list;

		SDL_AudioDeviceID device = SDL_OpenAudioDevice(
			0,
			0,
			&desired,
			&obtained,
			0);

		SDL_PauseAudioDevice(device, 0);
		callback_list->audio_device_id = device;
	}
}

void initialize_audio_capture(lb_BinaryS16* binary)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
	}
	else
	{
		SDL_AudioSpec desired;
		SDL_AudioSpec obtained;

		SDL_memset(&desired, 0, sizeof(desired));
		desired.freq = DEFAULT_STREAM_SAMPLE_FREQUENCY;
		desired.format = AUDIO_S16SYS;
		desired.channels = 1;
		desired.samples = DEFAULT_STREAM_SAMPLE_SIZE;
		desired.callback = (SDL_AudioCallback)run_callback_capture;
		desired.userdata = binary;

		SDL_AudioDeviceID device = SDL_OpenAudioDevice(
			0,
			1,
			&desired,
			&obtained,
			0);

		SDL_PauseAudioDevice(device, 0);
	}
}

void run_callback_play(void* userdata, Uint8* stream, int byte_length)
{
	/*Converts the 8-bit native stream to 16-bits and references
	a double-byte length that points to the stream samples as a collection
	of two bytes.*/
	Sint16* playback_stream = (Sint16*)stream;
	int double_byte_length = byte_length / sizeof(Sint16);
	CallbackList* callback_list = (CallbackList*)userdata;

	Sint16 debug_stream[DEFAULT_STREAM_SAMPLE_SIZE * 6] = { 0 };

	/*Clears stream after accumulating channels*/
	for (int i = 0; i < double_byte_length; i++)
	{
		playback_stream[i] = 0;
	}

	if (callback_list != 0)
	{
		for (int i = 0; i < callback_list->size; i++)
		{
			lb_Libretti* libretti = callback_list->libretti_list[i];

			if (libretti != 0 &&
				libretti->composition != 0 &&
				libretti->playback != 0 &&
				libretti->composition->track_count > 0)
			{
				lb_update_playback(libretti->playback, libretti->composition, DEFAULT_STREAM_SAMPLE_FREQUENCY);
				interleave_waveform_to_stream((int16_t*)playback_stream, libretti->playback, DEFAULT_STREAM_CHANNEL_COUNT);
			}
		}
	}
}

void run_callback_capture(void* userdata, Uint8* stream, int byte_length)
{
	/*Converts the 8-bit native stream to 16-bits and references
	a double-byte length that points to the stream samples as a collection
	of two bytes.*/
	Sint16* capture_stream = (Sint16*)stream;
	int double_byte_length = byte_length / sizeof(Sint16);
	lb_BinaryS16* binary = (lb_BinaryS16*)userdata;

	int16_t debug[DEFAULT_STREAM_SAMPLE_SIZE];

	for (int i = 0; i < binary->size; i++)
		binary->data[i] = capture_stream[i];

	for (int i = 0; i < binary->size; i++)
		debug[i] = binary->data[i];

	//debugging
	lb_append_binary_s16_to_file(binary, "audio_recording_dump.bin");
}

void finalize_audio_playback(CallbackList callback_list[])
{
	SDL_PauseAudioDevice(callback_list->audio_device_id, 1);
	SDL_CloseAudioDevice(callback_list->audio_device_id);
	SDL_CloseAudio();
	callback_list->audio_device_id = 0;
}

void finalize_callback()
{
	finalize_audio_playback(g_callback_list);
	free(g_callback_list);
	g_callback_list = 0;
}