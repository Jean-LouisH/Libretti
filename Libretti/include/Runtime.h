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

#include <stdint.h>
#include "UserControl.h"
#include <SDL_audio.h>

enum states
{
	IS_PLAYING = 1 << 0,
	PLAYED_ONCE = 1 << 1
};

typedef struct
{
	double currentPlayTime_s;
	uint32_t noteIndex[MAX_TRACKS];
	SDL_AudioDeviceID device;
	uint8_t playStates;
	lb_UserControl userControl;
}lb_Runtime;

#endif /*Runtime_h*/