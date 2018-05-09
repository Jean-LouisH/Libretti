/**
*                      This file is part of:
*                          Libretti
*
* Runtime
*
* Play runtime data for track position, playing, pausing, etc.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef Runtime_h
#define Runtime_h

#include <SDL_audio.h>

enum states
{
	IS_PLAYING = 1 << 0,
	PLAYED_ONCE = 1 << 1
};

typedef struct
{
	double currentPlayTime;
	SDL_AudioDeviceID device;
	unsigned char playStates;
}lb_Runtime;

#endif /*Runtime_h*/