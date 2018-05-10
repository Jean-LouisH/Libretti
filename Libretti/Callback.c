#include "include/Callback.h" 

#include "include/Libretti.h"

void runCallback(void* userdata, Uint8* stream, int byteLength)
{
	/*Converts the 8-bit native stream to 16-bits and references
	a double-byte length that points to the stream samples as a collection
	of two bytes.*/
	Sint16* callbackStream = (Sint16*)stream;
	int doubleByteLength = byteLength / sizeof(Sint16);
	lb_CallbackData* callbackData = (lb_CallbackData*)userdata;

	/*Clears stream after accumulating channels*/
	for (int i = 0; i < doubleByteLength; i++)
	{
		callbackStream[i] = 0;
	}

	if (callbackData->audio->trackCount > 0)
	{
		lb_updateNoteWavesFromAudio(callbackData->noteWaves, callbackData->audio);
	}
}