/**
*                      This file is part of:
*                          Libretti
*
* Mixer
*
* Applies effects to the note wave streams before sending to the audio device.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef Mixer_h
#define Mixer_h

#include "SDL_stdinc.h"
#include "NoteWaves.h"

void interleaveNoteWavesToStream(Sint16 outputStream[], lb_NoteWaves* noteWaves);

#endif /*Mixer_h*/