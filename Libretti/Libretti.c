#include "include/Libretti.h"

#include <SDL.h>
#include "include/ScriptValidator.h"
#include "include/Compiler.h"
#include "include/Callback.h"
#include "include/File.h"
#include "include/Mixer.h"
#include "include/CallbackList.h"
#include "include/WaveformGenerator.h"

static CallbackList* callbackList;

Libretti* lb_createLibretti(const char* filename)
{
	Libretti* libretti = malloc(sizeof *libretti);
	if (libretti != NULL)
	{
		libretti->audio = lb_createAudio(filename);
		libretti->noteWaves = lb_createNoteWaves();
		libretti->runtime = lb_createRuntime();
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

lb_NoteWaves* lb_createNoteWaves()
{
	return calloc(1, sizeof(lb_NoteWaves));
}

lb_Runtime* lb_createRuntime()
{
	return calloc(1, sizeof(lb_Runtime));
}

void lb_addLibrettiToCallback(Libretti* libretti)
{
	if (callbackList == NULL)
	{
		callbackList = calloc(1, sizeof(CallbackList));
		initAudioPlayback(callbackList);
	}
	
	//Checks for allocation after calloc()
	if (callbackList != NULL)
	{
		libretti->runtime->device = callbackList->device;
		libretti->runtime->playStates = 0;
		lb_reset(libretti);
		lb_play(libretti);
		callbackList->librettiList[callbackList->size] = libretti;
		callbackList->size++;
	}
}

Libretti* lb_createAndAddLibrettiToCallback(const char* filename)
{
	Libretti* libretti = lb_createLibretti(filename);
	if (libretti != NULL)
		lb_addLibrettiToCallback(libretti);
	return libretti;
}

int lb_validateScriptFile(const char* filename)
{
	char* script = loadBinaryFromFile(filename).data;
	int validationStatuses = validateScript(script);
	free(script);
	return validationStatuses;
}

void lb_compileAudioFromScriptFile(lb_Audio* audio, const char* filename)
{
	char* script = loadBinaryFromFile(filename).data;
	if (script != NULL)
	{
		compileAudioFromScript(audio, script);
		free(script);
	}
}

void lb_updateNoteWavesFromAudio(lb_NoteWaves* noteWaves, lb_Audio* audio, lb_Runtime* runtime)
{
	lb_Note* currentNotes = malloc(sizeof *currentNotes);
	lb_updateNotesFromAudio(currentNotes, audio, runtime);
	lb_updateNoteWavesFromNotes(noteWaves, currentNotes, audio->trackCount);
	free(currentNotes);
}

void lb_updateNotesFromAudio(lb_Note* currentNotes, lb_Audio* audio, lb_Runtime* runtime)
{

}

void lb_updateNoteWavesFromNotes(lb_NoteWaves* noteWaves, lb_Note* currentNotes, uint8_t trackCount)
{
	generateNoteWaves(noteWaves, currentNotes, trackCount);
}

void lb_incrementPlayTime(Libretti* libretti, double timeSeconds)
{
	if (libretti->runtime->playStates & IS_PLAYING)
	{
		libretti->runtime->currentPlayTime += timeSeconds;
	}
}

void lb_incrementAllPlayTimes(double timeSeconds)
{
	for (int i = 0; i < callbackList->size; i++)
	{
		Libretti* libretti = callbackList->librettiList[i];
		libretti->runtime->currentPlayTime += timeSeconds;
	}
}

void lb_load(Libretti* libretti, char* filename)
{
	lb_compileAudioFromScriptFile(libretti->audio, filename);
	lb_play(libretti->runtime);
}

void lb_play(Libretti* libretti)
{
	libretti->runtime->playStates |= IS_PLAYING;
	SDL_PauseAudioDevice(libretti->runtime->device, false);
}

void lb_pause(Libretti* libretti)
{
	libretti->runtime->playStates &= ~IS_PLAYING;
	SDL_PauseAudioDevice(libretti->runtime->device, true);
}

void lb_reset(Libretti* libretti)
{
	libretti->runtime->currentPlayTime = 0.0;
}

void lb_stop(Libretti* libretti)
{
	lb_reset(libretti->runtime);
	lb_pause(libretti->runtime);
}

void lb_playAll()
{
	for (int i = 0; i < callbackList->librettiList; i++)
		lb_play(callbackList->librettiList[i]);
}

void lb_pauseAll()
{
	for (int i = 0; i < callbackList->librettiList; i++)
		lb_pause(callbackList->librettiList[i]);
}

void lb_resetAll()
{
	for (int i = 0; i < callbackList->librettiList; i++)
		lb_reset(callbackList->librettiList[i]);
}

void lb_stopAll()
{
	for (int i = 0; i < callbackList->librettiList; i++)
		lb_stop(callbackList->librettiList[i]);
}

void lb_exportAudioToWAV(lb_Audio* audio, const char* name)
{

}

void lb_freeRuntime(lb_Runtime* runtime)
{
	SDL_CloseAudioDevice(runtime->device);
	free(runtime);
}

void lb_freeNoteWaves(lb_NoteWaves* noteWaves)
{
	free(noteWaves);
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
}

void lb_freeLibretti(Libretti* libretti)
{
	lb_freeRuntime(libretti->runtime);
	lb_freeNoteWaves(libretti->noteWaves);
	lb_freeAudio(libretti->audio);
	libretti->runtime = NULL;
	libretti->noteWaves = NULL;
	libretti->audio = NULL;
	free(libretti);
}