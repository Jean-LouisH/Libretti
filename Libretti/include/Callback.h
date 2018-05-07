/**
*                      This file is part of:
*                          Libretti
*
* Callback
*
* Handles the audio thread and communicates with the main thread.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef Callback_h
#define Callback_h

#include <SDL.h>
#include "Audio.h"
#include "NoteWaves.h"

/** SDL's audio callback in this case relies on pointers
* for data sharing with the main thread.*/
typedef struct
{
	lb_Audio* audio;
	lb_NoteWaves* noteWaves;
}lb_CallbackData;

void runCallback(void* userdata, Uint8* stream, int byteLength);

#endif /*Callback_h*/