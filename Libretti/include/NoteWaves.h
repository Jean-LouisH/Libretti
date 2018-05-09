/**
*                      This file is part of:
*                          Libretti
*
* NoteWaves
*
* Raw audio samples from individual notes.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef NoteWaves_h
#define NoteWaves_h

#include "SDL_stdinc.h"
#include "Constants.h"
#include "Notes.h"

typedef struct
{
	Sint16 streams[MAX_TRACKS][SAMPLE_SIZE(SAMPLES_PER_FRAME)];
	lb_Note metaData[MAX_TRACKS];
	unsigned char count;
}lb_NoteWaves;

#endif /*NoteWaves_h*/