#include "include/Libretti.h"

#include <SDL.h>
#include "include/Compiler.h"
#include "include/Callback.h"
#include "include/File.h"
#include "include/Mixer.h"
#include "include/WaveformGenerator.h"

int lb_libraryCompilationTest()
{
	int a = 0;
	a++;
	char* q = loadScriptFromFile("../Demos/Single channel Test.txt");
	return a;
}

Libretti* lb_createLibretti()
{
	Libretti* libretti = malloc(sizeof *libretti);
	if (libretti != NULL)
	{
		libretti->audio = lb_createAudio();
		libretti->noteWaves = lb_createNoteWaves();
		libretti->callbackData = lb_createCallbackData();
		libretti->runtime = lb_createRuntime();

		if (libretti->audio != NULL &&
			libretti->callbackData != NULL &&
			libretti->noteWaves != NULL &&
			libretti->runtime != NULL)
		{
			lb_initCallbackData(libretti->callbackData, libretti->audio, libretti->noteWaves, libretti->runtime);
			lb_initAudioCallback(libretti->runtime, libretti->callbackData);
		}
	}
	return libretti;
}

lb_Audio* lb_createAudio()
{
	return calloc(1, sizeof(lb_Audio));
}

lb_NoteWaves* lb_createNoteWaves()
{
	return calloc(1, sizeof(lb_NoteWaves));
}

lb_CallbackData* lb_createCallbackData()
{
	return calloc(1, sizeof(lb_CallbackData));
}

lb_Runtime* lb_createRuntime()
{
	return calloc(1, sizeof(lb_Runtime));
}

void lb_initCallbackData(lb_CallbackData* callbackData, lb_Audio* audio, lb_NoteWaves* noteWaves, lb_Runtime* runtime)
{
	callbackData->audio = audio;
	callbackData->noteWaves = noteWaves;
	callbackData->runtime = runtime;
}

void lb_initAudioCallback(lb_CallbackData* callbackData)
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
		desired.freq = SAMPLE_FREQUENCY;
		desired.format = AUDIO_S16SYS;
		desired.channels = CHANNELS;
		desired.samples = SAMPLE_SIZE;
		desired.callback = (SDL_AudioCallback)runCallback;
		desired.userdata = callbackData;

		SDL_AudioDeviceID device = SDL_OpenAudioDevice(
			NULL,
			0,
			&desired,
			&obtained,
			NULL);

		callbackData->runtime->device = device;
		callbackData->runtime->playStates = 0;
		lb_reset(callbackData->runtime);
		lb_play(callbackData->runtime);
	}
}

void lb_compileAudioFromScriptFile(lb_Audio* audio, char* filename)
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

void lb_freeCallbackData(lb_CallbackData* callbackData)
{
	free(callbackData);
}

void lb_freeNoteWaves(lb_NoteWaves* noteWaves)
{
	free(noteWaves);
}

void lb_freeAudio(lb_Audio* audio)
{
	if (audio->tracks->notes != NULL)
		free(audio->tracks->notes);
	if (audio->tempos != NULL)
		free(audio->tempos);
	if (audio->lyricsLines != NULL)
		free(audio->lyricsLines);
	free(audio);
}

void lb_freeLibretti(Libretti* libretti)
{
	lb_freeRuntime(libretti->runtime);
	lb_freeCallbackData(libretti->callbackData);
	lb_freeNoteWaves(libretti->noteWaves);
	lb_freeAudio(libretti->audio);
	free(libretti);
}