#include "include/Libretti.h"

#include <SDL.h>
#include "include/ScriptValidator.h"
#include "include/Compiler.h"
#include "include/Callback.h"
#include "include/File.h"
#include "include/Mixer.h"
#include "include/CallbackList.h"
#include "include/WaveformGenerator.h"

int lb_libraryCompilationTest()
{
	int a = 0;
	a++;
	char* q = loadScriptFromFile("../Demos/Mary had a little lamb (feature test).txt");
	return a;
}

Libretti* lb_createLibretti(const char* filename)
{
	Libretti* libretti = calloc(1, sizeof *libretti);
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
	static CallbackList* callbackList;

	if (callbackList == NULL)
	{
		callbackList = calloc(1, sizeof(CallbackList));
		initAudioCallback(callbackList);
	}
	
	//Checks for allocation after calloc()
	if (callbackList != NULL)
	{
		libretti->runtime->device = callbackList->device;
		libretti->runtime->playStates = 0;
		lb_reset(libretti->runtime);
		lb_play(libretti->runtime);
		callbackList->librettiList[callbackList->size] = libretti;
		callbackList->size++;
	}
}

int lb_validateScriptFile(const char* filename)
{
	char* script = loadScriptFromFile(filename);
	validateScript(script);
	free(script);
}

void lb_compileAudioFromScriptFile(lb_Audio* audio, const char* filename)
{
	char* script = loadScriptFromFile(filename);
	if (script != NULL)
	{
		compileAudioFromScript(audio, script);
		free(script);
	}
}

void lb_updateNoteWavesFromAudio(lb_NoteWaves* noteWaves, lb_Audio* audio)
{

}

void lb_updateNotesFromAudio(lb_Note* notes, unsigned char* noteCount, lb_Audio* audio)
{

}

void lb_updateNoteWavesFromNotes(lb_NoteWaves* noteWaves, lb_Note* notes, unsigned char* noteCount)
{

}

void lb_incrementPlayTime(lb_Runtime* runtime, double timeSeconds)
{
	if (runtime->playStates & IS_PLAYING)
	{
		runtime->currentPlayTime += timeSeconds;
	}
}

void lb_load(lb_Runtime* runtime, lb_Audio* audio, char* filename)
{
	lb_compileAudioFromScriptFile(audio, filename);
	lb_play(runtime);
}

void lb_play(lb_Runtime* runtime)
{
	runtime->playStates |= IS_PLAYING;
	SDL_PauseAudioDevice(runtime->device, 0);
}

void lb_pause(lb_Runtime* runtime)
{
	runtime->playStates &= ~IS_PLAYING;
	SDL_PauseAudioDevice(runtime->device, 1);
}

void lb_reset(lb_Runtime* runtime)
{
	runtime->currentPlayTime = 0.0;
}

void lb_stop(lb_Runtime* runtime)
{
	lb_reset(runtime);
	lb_pause(runtime);
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
	if (audio->tracks->notes != NULL)
		free(audio->tracks->notes);
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
	free(libretti);
}