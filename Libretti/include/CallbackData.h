/**
*                      This file is part of:
*                          Libretti
*
* Callback data
*
* Contains the audio and note wave memory locations for callback.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef CallbackData_h
#define CallbackData_h

#include "Audio.h"
#include "NoteWaves.h"

/** SDL's audio callback in this case relies on pointers
* for data sharing with the main thread.*/
typedef struct
{
	lb_Audio* audio;
	lb_NoteWaves* noteWaves;
}lb_CallbackData;

#endif /*CallbackData_h*/