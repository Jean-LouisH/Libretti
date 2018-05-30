/**
*                      This file is part of:
*                          Libretti
*
* Waveform Generator
*
* Provides note waves from notes.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef WaveformGenerator_h
#define WaveformGenerator_h

#include "Notes.h"
#include "NoteWaves.h"

void generateNoteWaves(lb_NoteWaves* noteWaves, lb_Note* currentNotes, unsigned char* trackCount);

#endif /*WaveformGenerator_h*/