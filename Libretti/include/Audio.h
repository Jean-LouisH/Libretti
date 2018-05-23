/**
*                      This file is part of:
*                          Libretti
*
* Audio
*
* Defines entire songs or sound effects in memory.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef Audio_h
#define Audio_h

#include "Constants.h"
#include "Events.h"
#include "Tracks.h"

typedef struct
{
	lb_Track tracks[MAX_TRACKS];
	lb_TempoEvent* tempoEvents;
	lb_LyricsEvent* lyricsEvents;
	unsigned char trackCount;
	unsigned char tempoEventCount;
	unsigned char lyricsEventCount;
	double timeLength;
	double loopTargetTime;
	char* name;
	char* artist;
	unsigned char keySignature;		
	unsigned char timeSignature[2]; //[0] = numerator, [1] = denominator
}lb_Audio;

#endif /*Audio_h*/