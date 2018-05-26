#include "include/Callback.h" 
#include "include/CallbackList.h"
#include <SDL.h>

void initAudioCallback(CallbackList* callbackList)
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
		desired.userdata = callbackList;

		SDL_AudioDeviceID device = SDL_OpenAudioDevice(
			NULL,
			0,
			&desired,
			&obtained,
			NULL);

		callbackList->device = device;
	}
}

void runCallback(void* userdata, Uint8* stream, int byteLength)
{
	/*Converts the 8-bit native stream to 16-bits and references
	a double-byte length that points to the stream samples as a collection
	of two bytes.*/
	Sint16* callbackStream = (Sint16*)stream;
	int doubleByteLength = byteLength / sizeof(Sint16);
	CallbackList* callbackList = (CallbackList*)userdata;

	/*Clears stream after accumulating channels*/
	for (int i = 0; i < doubleByteLength; i++)
	{
		callbackStream[i] = 0;
	}

	for (int i = 0; i < callbackList->size; i++)
	{
		Libretti* libretti = callbackList->librettiList[i];
		if (libretti->audio->trackCount > 0)
		{
			lb_updateNoteWavesFromAudio(libretti->noteWaves, libretti->audio);
		}
	}
}