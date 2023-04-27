/**
*                      This file is part of:
*                          Libretti
*
* Runtime
*
* Play runtime data for track position, playing, pausing, etc.
*
* Copyright (c) 2017-2021 Jean-Louis Haywood. All rights reserved.
*/

#ifndef Runtime_h
#define Runtime_h

#include <stdint.h>
#include "UserEffectsOverride.h"
#include <SDL_audio.h>

enum states
{
	LB_RUNTIME_STATE_IS_PLAYING = 1 << 0,
	LB_RUNTIME_STATE_PLAYED_AT_LEAST_ONCE = 1 << 1
};

typedef struct
{
	float currentPlayTime; //in seconds
	uint32_t trackNoteIndices[MAX_TRACKS];
	SDL_AudioDeviceID device;
	uint8_t playStates;
	uint16_t currentLoopCount;
	lb_UserEffectsOverride userEffectsOverride;
}lb_Runtime;

#endif /*Runtime_h*/