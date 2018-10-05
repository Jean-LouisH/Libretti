/**
*                      This file is part of:
*                          Libretti
*
* Events
*
* Track components with timestamps.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef Events_h
#define Events_h

#include "Notes.h"

typedef struct
{
	lb_Note note;
	double startTime_s;
}lb_NoteEvent;

typedef struct
{
	unsigned char tempo_bpm;
	double startTime_s;
}lb_TempoEvent;

typedef struct
{
	char* lyrics;
	double startTime_s;
}lb_LyricsEvent;

#endif /*Events_h*/