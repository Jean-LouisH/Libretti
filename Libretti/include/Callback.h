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

#include <SDL_stdinc.h>
#include "CallbackList.h"

void initAudioPlayback(CallbackList* callbackList);
void initAudioCapture();
void runCallbackPlay(void* userdata, Uint8* stream, int byteLength);
void runCallbackCapture(void* userdata, Uint8* stream, int byteLength);

#endif /*Callback_h*/