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
	double startTime;
}lb_NoteEvent;

typedef struct
{
	unsigned char tempo;
	double startTime;
}lb_TempoEvent;

typedef struct
{
	char* lyrics;
	double startTime;
}lb_LyricsEvent;

#endif /*Events_h*/