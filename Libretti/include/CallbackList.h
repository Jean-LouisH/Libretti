/**
*                      This file is part of:
*                          Libretti
*
* Callback List
*
* Contains references to all actively played Libretti structs.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef CallbackList_h
#define CallbackList_h

#include "Libretti.h"
#include <SDL_audio.h>

typedef struct
{
	Libretti** librettiList;
	SDL_AudioDeviceID device;
	unsigned char size;
}CallbackList;

#endif /*CallbackList_h*/