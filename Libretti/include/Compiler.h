/**
*                      This file is part of:
*                          Libretti
*
* Compiler
*
* Builds the audio structs from text scripts.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef Compiler_h
#define Compiler_h

#include "Audio.h"

void compileAudioFromScript(lb_Audio* audio, char* script);
void validateScript(char* script);
void allocateMemory(lb_Audio* audio, char* script);
void buildAudioData(lb_Audio* audio, char* script);
void tuneByKeySignature(lb_Audio* audio, char* noteChar);
void assignFrequencyFromNoteChar(lb_Note note, char noteChar);
void tuneByAccidental(lb_Note note, char noteChar);
void assignDurationValue(lb_Audio* audio, char* script);

#endif /*Compiler_h*/