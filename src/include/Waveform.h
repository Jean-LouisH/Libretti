/**
*                      This file is part of:
*                          Libretti
*
* Waveform
*
* Raw audio samples from individual notes.
*
* Copyright (c) 2017-2021 Jean-Louis Haywood. All rights reserved.
*/

#ifndef Waveform_h
#define Waveform_h

#include <stdint.h>
#include "SDL_stdinc.h"
#include "Constants.h"
#include "Notes.h"

typedef struct
{
	Sint16 streams[MAX_TRACKS][SAMPLE_SIZE];
	lb_Note metaData[MAX_TRACKS];
	uint8_t count;
}lb_Waveform;

#endif /*Waveform_h*/