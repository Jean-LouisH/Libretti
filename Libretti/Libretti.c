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

void lb_initLibretti(Libretti* libretti)
{
	lb_initCallbackData(&libretti->callbackData, &libretti->audio, &libretti->noteWaves);
	lb_initAudioRuntime(&libretti->runtime, &libretti->callbackData);
}

void lb_initCallbackData(lb_CallbackData* callbackData, lb_Audio* audio, lb_NoteWaves* noteWaves)
{
	callbackData->audio = audio;
	callbackData->noteWaves = noteWaves;
}

void lb_initAudioRuntime(lb_Runtime* runtime, lb_CallbackData* callbackData)
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

		runtime->device = device;
		lb_play(runtime);
	}
}

void lb_compileAudioFromScriptFile(lb_Audio* audio, char* filename)
{
	char* script = loadScriptFromFile(filename);
	compileAudioFromScript(audio, script);
	free(script);
}

void lb_updateNotesFromAudio(lb_Note* notes, unsigned char* noteCount, lb_Audio* audio)
{

}

void lb_updateNoteWavesFromAudio(lb_NoteWaves* noteWaves, lb_Audio* audio)
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

void lb_freeLibretti(Libretti* libretti)
{
	SDL_CloseAudioDevice(libretti->runtime.device);
}