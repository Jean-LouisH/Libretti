/**
*                      This file is part of:
*                          Libretti
*
* Tracks
*
* Individual tracks of notes that comprise audio structs.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef Tracks_h
#define Tracks_h

#include "Events.h"

typedef struct
{
	lb_NoteEvent* notes;
	unsigned int noteCount;
}lb_Track;

#endif /*Tracks_h*/