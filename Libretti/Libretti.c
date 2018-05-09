#include "include/Libretti.h"

#include "include/Compiler.h"
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

void lb_initCallbackData(lb_CallbackData* callbackData, lb_Audio* audio, lb_NoteWaves* noteWaves)
{
	callbackData->audio = audio;
	callbackData->noteWaves = noteWaves;
}

void lb_initAudioRuntime(lb_Runtime* runtime, lb_CallbackData* callbackData, void* callback)
{

}

void lb_compileAudioFromScript(lb_Audio* audio, char* filename)
{
	char* script = loadScriptFromFile(filename);
	compileAudioFromScript(audio, script);
	free(script);
}

void lb_updateNotesFromAudio(lb_Note* notes, lb_Audio* audio)
{

}

void lb_updateNoteWavesFromAudio(lb_NoteWaves* noteWaves, lb_Audio* audio)
{

}

void lb_updateNoteWavesFromNotes(lb_NoteWaves* noteWaves, lb_Note* notes)
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

}

void lb_play(lb_Runtime* runtime)
{
	runtime->playStates |= IS_PLAYING;
	SDL_PauseAudioDevice(runtime->device, 1);
}

void lb_pause(lb_Runtime* runtime)
{
	runtime->playStates &= ~IS_PLAYING;
	SDL_PauseAudioDevice(runtime->device, 0);
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