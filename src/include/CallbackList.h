/**
*                      This file is part of:
*                          Libretti
*
* Callback List
*
* Contains references to all actively played Libretti structs.
*
* Copyright (c) 2017-2021 Jean-Louis Haywood. All rights reserved.
*/

#ifndef CallbackList_h
#define CallbackList_h

#include "Libretti.h"
#include <SDL_audio.h>

typedef struct
{
	lb_Libretti** librettiList;
	SDL_AudioDeviceID device;
	int size;
	int capacity;
}CallbackList;

#endif /*CallbackList_h*/