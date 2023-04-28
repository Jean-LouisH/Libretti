#include "include/Libretti.h"

#include <SDL.h>
#include "include/ScriptValidator.h"
#include "include/Compiler.h"
#include "include/Callback.h"
#include "include/File.h"
#include "include/Mixer.h"
#include "include/CallbackList.h"
#include "include/WaveformGenerator.h"

static CallbackList* g_callbackList = NULL;
static int g_librettiIDCount = -1;

void lb_initialize()
{
	if (g_callbackList == NULL)
	{
		g_callbackList = calloc(1, sizeof(CallbackList));
		if (g_callbackList != NULL)
		{
			g_librettiIDCount = 0;
			g_callbackList->capacity = 2;
			g_callbackList->librettiList = calloc(g_callbackList->capacity, sizeof(lb_Libretti*));
			initAudioPlayback(g_callbackList);
		}
		else
		{
			g_librettiIDCount = -1;
		}
	}
}

lb_Libretti* lb_createLibretti(const char* filename)
{
	lb_Libretti* libretti = malloc(sizeof *libretti);
	if (libretti != NULL)
	{
		libretti->audio = lb_createAudio(filename);
		libretti->noteWaves = lb_createNoteWaves();
		libretti->runtime = lb_createRuntime();
		if (g_librettiIDCount != -1)
		{
			libretti->id = g_librettiIDCount;
			g_librettiIDCount++;
		}
	}
	return libretti;
}

lb_Libretti* lb_createEmptyLibretti()
{
	lb_Libretti* libretti = malloc(sizeof *libretti);
	if (libretti != NULL)
	{
		libretti->audio = lb_createEmptyAudio();
		libretti->noteWaves = lb_createNoteWaves();
		libretti->runtime = lb_createRuntime();
		if (g_librettiIDCount != -1)
		{
			libretti->id = g_librettiIDCount;
			g_librettiIDCount++;
		}
	}
	return libretti;
}

lb_Audio* lb_createAudio(const char* filename)
{
	lb_Audio* audio = calloc(1, sizeof(lb_Audio));
	if (audio != NULL)
		lb_compileAudioFromScriptFile(audio, filename);
	return audio;
}

lb_Audio* lb_createEmptyAudio()
{
	return calloc(1, sizeof(lb_Audio));
}

lb_NoteWaves* lb_createNoteWaves()
{
	return calloc(1, sizeof(lb_NoteWaves));
}

lb_Runtime* lb_createRuntime()
{
	return calloc(1, sizeof(lb_Runtime));
}

void lb_addLibrettiToCallback(lb_Libretti* libretti)
{
	if (g_callbackList != NULL)
	{
		libretti->runtime->device = g_callbackList->device;
		libretti->runtime->playStates = 0;
		libretti->runtime->currentLoopCount = 0;
		libretti->runtime->userEffectsOverride.outputVolume = 1.0;
		libretti->runtime->userEffectsOverride.outputPanning = 0.0;
		lb_reset(libretti);
		lb_play(libretti);

		/* Expand the CallbackList when it gets full.*/
		if (g_callbackList->size == g_callbackList->capacity - 1)
		{
			int newCapacity = g_callbackList->capacity * 2;
			g_callbackList->librettiList = realloc(g_callbackList->librettiList, newCapacity * sizeof(lb_Libretti*));
			if (g_callbackList->librettiList != NULL)
				g_callbackList->capacity = newCapacity;
		}

		/* If the capacity expansion were successful, add the Libretti
		 * to the end of the list.*/
		if (g_callbackList->size < g_callbackList->capacity - 1)
		{
			g_callbackList->librettiList[g_callbackList->size] = libretti;
			g_callbackList->size++;
		}
	}
}

void lb_removeLibrettiFromCallback(int librettiID)
{
	if (g_callbackList != NULL)
	{
		if (g_callbackList->librettiList != NULL)
		{
			/*Simple linear search implementation since they're not intended
			 * to be much larger than 10 at a time.*/
			for (int i = 0; i < g_callbackList->size; i++)
			{
				if (g_callbackList->librettiList[i]->id == librettiID)
				{
					/* If it's not the last entry, swap and shuffle all the later entries
					 * to the front of the list.*/
					for (int j = i; j < g_callbackList->size - 1; j++)
					{
						g_callbackList->librettiList[j] = g_callbackList->librettiList[j + 1];
					}

					g_callbackList->librettiList[g_callbackList->size - 1] = NULL;
					g_callbackList->size--;
					break;
				}
			}
		}
	}
}

lb_Libretti* lb_createAndAddLibrettiToCallback(const char* filename)
{
	lb_Libretti* libretti = lb_createLibretti(filename);
	if (libretti != NULL)
		lb_addLibrettiToCallback(libretti);
	return libretti;
}

lb_Libretti* lb_createAndAddEmptyLibrettiToCallback()
{
	lb_Libretti* libretti = lb_createEmptyLibretti();
	if (libretti != NULL)
		lb_addLibrettiToCallback(libretti);
	return libretti;
}

int lb_validateScriptFile(const char* filename)
{
	char* script = loadASCIIStringFromFile(filename).data;
	int validationStatuses = validateScript(script);
	free(script);
	return validationStatuses;
}

void lb_compileAudioFromScriptFile(lb_Audio* audio, const char* filename)
{
	char* script = loadASCIIStringFromFile(filename).data;
	if (script != NULL)
	{
		compileAudioFromScript(audio, script);
		free(script);
	}
}

void lb_updateNoteWavesFromAudio(lb_NoteWaves* noteWaves, lb_Audio* audio, lb_Runtime* runtime)
{
	lb_Note* currentNotes = malloc(audio->trackCount * (sizeof *currentNotes));
	lb_updateNotesFromAudio(currentNotes, audio, runtime);
	noteWaves->count = audio->trackCount;
	lb_updateNoteWavesFromNotes(noteWaves, currentNotes, audio->trackCount);
	free(currentNotes);
}

void lb_updateNotesFromAudio(lb_Note currentNotes[], lb_Audio* audio, lb_Runtime* runtime)
{
	for (int i = 0; i < audio->trackCount; i++)
	{
		/*Prevents note searches on lyrics audio scopes*/
		if (audio->tracks[i].noteCount > 0)
		{
			lb_NoteEvent noteEvent = audio->tracks[i].noteEvents[runtime->trackNoteIndices[i]];
			lb_Note silentNote = { 0 };
			lb_NoteEvent nextNoteEvent;

			if (runtime->trackNoteIndices[i] < audio->tracks[i].noteCount - 1)
			{
				nextNoteEvent = audio->tracks[i].noteEvents[runtime->trackNoteIndices[i] + 1];
			}
			else
			{
				nextNoteEvent.note = silentNote;
				nextNoteEvent.startTime = audio->timeLength;
			}

			/*Find and set the current note to play*/
			while ((runtime->currentPlayTime > nextNoteEvent.startTime))
			{
				if (runtime->trackNoteIndices[i] < audio->tracks[i].noteCount - 1)
				{
					runtime->trackNoteIndices[i]++;
					noteEvent = audio->tracks[i].noteEvents[runtime->trackNoteIndices[i]];
					nextNoteEvent = audio->tracks[i].noteEvents[runtime->trackNoteIndices[i] + 1];
				}
				else
				{
					nextNoteEvent.note = silentNote;
					nextNoteEvent.startTime = audio->timeLength;
				}

				/*Reset the song when the time exceeds the last time stamp.*/
				if (runtime->currentPlayTime > audio->timeLength)
				{
					runtime->playStates |= LB_RUNTIME_STATE_PLAYED_AT_LEAST_ONCE;
					runtime->currentLoopCount++;

					if ((runtime->currentLoopCount < audio->loopCount) ||
						audio->loopCount == pow(2, (sizeof audio->loopCount) * 8) - 1)
					{
						runtime->currentPlayTime = audio->loopTimestamp;

						for (int j = 0; j < audio->trackCount; j++)
						{
							runtime->trackNoteIndices[j] = 0;

							/*Find and set note indices to loop time stamps.*/
							while (audio->loopTimestamp > 
								audio->tracks[j].noteEvents[runtime->trackNoteIndices[j]].startTime)
							{
								runtime->trackNoteIndices[j]++;
							}
						}
					}
					else
					{
						runtime->playStates &= ~LB_RUNTIME_STATE_IS_PLAYING;
						SDL_PauseAudioDevice(runtime->device, true);
					}
				}	
			}

			const float slurTimeRatio = 1.0;
			const float normalTimeRatio = 0.85;
			const float staccatoTimeRatio = 0.15;

			float currentTimeRatio = normalTimeRatio;

			switch (noteEvent.note.articulation)
			{
				case LB_ARTICULATION_SLUR: currentTimeRatio = slurTimeRatio; break;
				case LB_ARTICULATION_NORMAL: currentTimeRatio = normalTimeRatio; break;
				case LB_ARTICULATION_STACCATO: currentTimeRatio = staccatoTimeRatio; break;
			}

			float noteLiftTime = (noteEvent.startTime +
				((nextNoteEvent.startTime - noteEvent.startTime) * currentTimeRatio));

			if (runtime->currentPlayTime > noteLiftTime)
			{
				currentNotes[i] = silentNote;
			}
			else
			{
				currentNotes[i] = audio->tracks[i].noteEvents[runtime->trackNoteIndices[i]].note;
			}
		}
	}
}

void lb_updateNoteWavesFromNotes(lb_NoteWaves* noteWaves, lb_Note currentNotes[], uint8_t trackCount)
{
	generateNoteWaves(noteWaves, currentNotes);
}

void lb_incrementPlayTime(lb_Libretti* libretti, float deltaTime_s)
{
	if (libretti->runtime->playStates & LB_RUNTIME_STATE_IS_PLAYING)
		libretti->runtime->currentPlayTime += deltaTime_s;
}

void lb_incrementAllPlayTimes(float deltaTime_s)
{
	if (g_callbackList != NULL)
	{
		for (int i = 0; i < g_callbackList->size; i++)
		{
			lb_Libretti* libretti = g_callbackList->librettiList[i];
			lb_incrementPlayTime(libretti, deltaTime_s);
		}
	}
}

void lb_load(lb_Libretti* libretti, const char* filename)
{
	lb_compileAudioFromScriptFile(libretti->audio, filename);
	lb_play(libretti);
}

void lb_play(lb_Libretti* libretti)
{
	libretti->runtime->playStates |= LB_RUNTIME_STATE_IS_PLAYING;
	SDL_PauseAudioDevice(libretti->runtime->device, false);
}

lb_Libretti* lb_play_note_for(
	uint16_t key,
	uint16_t dynamic,
	uint8_t panning,
	uint8_t timbre,
	uint8_t articulation,
	float duration)
{
	lb_Libretti* libretti = lb_createEmptyLibretti();
	lb_Audio* audio = libretti->audio;
	audio->trackCount = 1;
	audio->tracks[0].noteEvents = calloc(1, sizeof(lb_NoteEvent));

	if (audio->tracks[0].noteEvents != NULL)
	{
		audio->tracks[0].noteCount = 1;
		audio->tracks[0].noteEvents->startTime = 0.0;
		audio->tracks[0].noteEvents->note.dynamic = dynamic;
		audio->tracks[0].noteEvents->note.articulation = articulation;
		audio->tracks[0].noteEvents->note.key = key;
		audio->tracks[0].noteEvents->note.panning = panning;
		audio->tracks[0].noteEvents->note.timbre = timbre;
		audio->keySignature = LB_KEY_SIGNATURE_C_MAJOR;
		audio->loopCount = 0;
		audio->loopTimestamp = 0.0;
		audio->lyricsEventCount = 0;
		audio->tempoEventCount = 0;
		audio->timeLength = duration;
		audio->timeSignature[0] = 4;
		audio->timeSignature[1] = 4;
		lb_addLibrettiToCallback(libretti);
	}

	return libretti;
}

lb_Libretti* lb_play_note(
	uint16_t key,
	uint16_t dynamic,
	uint8_t panning,
	uint8_t timbre)
{
	return lb_play_note_for(
		key,
		dynamic,
		panning,
		timbre,
		LB_ARTICULATION_NORMAL,
		INFINITY);
}

lb_Libretti* lb_play_simple_note_for(
	uint16_t key,
	uint16_t dynamic,
	float duration)
{
	return lb_play_note_for(
		key,
		dynamic,
		LB_PANNING_CENTRE,
		LB_TIMBRE_SQUARE_WAVE,
		LB_ARTICULATION_NORMAL,
		duration);
}

lb_Libretti* lb_play_simple_note(
	uint16_t key,
	uint16_t dynamic)
{
	return lb_play_simple_note_for(
		key,
		dynamic,
		INFINITY);
}

void lb_pause(lb_Libretti* libretti)
{
	libretti->runtime->playStates &= ~LB_RUNTIME_STATE_IS_PLAYING;
	SDL_PauseAudioDevice(libretti->runtime->device, true);
}

void lb_reset(lb_Libretti* libretti)
{
	libretti->runtime->currentPlayTime = 0.0;
	for (int i = 0; i < MAX_TRACKS; i++)
		libretti->runtime->trackNoteIndices[i] = 0;
}

void lb_stop(lb_Libretti* libretti)
{
	lb_reset(libretti);
	lb_pause(libretti);
}

void lb_playAll()
{
	for (int i = 0; i < g_callbackList->librettiList; i++)
		lb_play(g_callbackList->librettiList[i]);
}

void lb_pauseAll()
{
	for (int i = 0; i < g_callbackList->librettiList; i++)
		lb_pause(g_callbackList->librettiList[i]);
}

void lb_resetAll()
{
	for (int i = 0; i < g_callbackList->librettiList; i++)
		lb_reset(g_callbackList->librettiList[i]);
}

void lb_stopAll()
{
	for (int i = 0; i < g_callbackList->librettiList; i++)
		lb_stop(g_callbackList->librettiList[i]);
}

lb_BinaryS16* lb_getAudioCaptureStreamBuffer()
{
	lb_BinaryS16* binary = calloc(1, sizeof *binary);
	if (binary != NULL)
	{
		binary->size = SAMPLE_SIZE;
		binary->data = calloc(SAMPLE_SIZE, sizeof * binary->data);
		initAudioCapture(binary);
	}
	return binary;
}

void lb_saveBinaryU8ToFile(lb_BinaryU8* binary, const char* filename)
{
	saveBinaryU8ToFile(binary, (char*)filename);
}

void lb_saveBinaryS16ToFile(lb_BinaryS16* binary, const char* filename)
{
	saveBinaryS16ToFile(binary, (char*)filename);
}

void lb_appendBinaryU8ToFile(lb_BinaryU8* binary, const char* filename)
{
	appendBinaryU8ToFile(binary, (char*)filename);
}

void lb_appendBinaryS16ToFile(lb_BinaryS16* binary, const char* filename)
{
	appendBinaryS16ToFile(binary, (char*)filename);
}

void lb_exportAudioToWAV(lb_Audio* audio, const char* name)
{
	lb_Runtime* exportRuntime = lb_createRuntime();
	lb_NoteWaves* exportNoteWaves = lb_createNoteWaves();
	lb_BinaryS16 exportBinary;

	int maxNoteCount = 0;

	for (int i = 0; i < audio->trackCount; i++)
		if (audio->tracks[i].noteCount > maxNoteCount)
			maxNoteCount = audio->tracks[i].noteCount;

	int streamLength = maxNoteCount * SAMPLE_SIZE;
	exportBinary.data = calloc(streamLength, sizeof(int16_t));

	/*Building the export binary stream*/
	while (!(exportRuntime->playStates & LB_RUNTIME_STATE_PLAYED_AT_LEAST_ONCE))
	{
		int streamPosition = 0;
		lb_updateNoteWavesFromAudio(exportNoteWaves, audio, exportRuntime);
		for (int i = 0; i < SAMPLE_SIZE; i++)
		{
			exportBinary.data[streamPosition] += exportNoteWaves->streams[0][i];
			streamPosition++;
		}
		exportRuntime->currentPlayTime += 17.0 / 1000.0;
	}


	/*Exporting to WAV file*/

}

void lb_freeRuntime(lb_Runtime* runtime)
{
	SDL_CloseAudioDevice(runtime->device);
	free(runtime);
	runtime = NULL;
}

void lb_freeNoteWaves(lb_NoteWaves* noteWaves)
{
	free(noteWaves);
	noteWaves = NULL;
}

void lb_freeAudio(lb_Audio* audio)
{
	if (audio->tracks->noteEvents != NULL)
		free(audio->tracks->noteEvents);
	if (audio->tempoEvents != NULL)
		free(audio->tempoEvents);
	if (audio->lyricsEvents != NULL)
		free(audio->lyricsEvents);
	free(audio);
	audio = NULL;
}

void lb_freeLibretti(lb_Libretti* libretti)
{
	lb_freeRuntime(libretti->runtime);
	lb_freeNoteWaves(libretti->noteWaves);
	lb_freeAudio(libretti->audio);
	libretti->runtime = NULL;
	libretti->noteWaves = NULL;
	libretti->audio = NULL;
	free(libretti);
	libretti = NULL;
}

void lb_finalize()
{
	finalizeAudioPlayback(g_callbackList);
	free(g_callbackList);
	g_callbackList = NULL;
}