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

enum compilationStatuses
{
	ALL_OK,
	NO_TRACK_SCOPE_DETECTED,
	NO_TIME_SIG_PROVIDED,
	UNCLOSED_TRACK_SCOPE,
	UNEXPECTED_HEADER_NAME,
	UNEXPECTED_HEADER_VALUE,
	UNKNOWN_SYMBOL,
	BEATS_DO_NOT_MATCH_TIME_SIG,
	BARS_COUNTS_DO_NOT_MATCH,
	OCTAVE_SHIFTS_OUT_OF_RANGE,
	UNCLOSED_HEADER_TAG,
	UNCLOSED_TUPLET,
	UNCLOSED_SLUR,
	UNCLOSED_CRESCENDO,
	UNCLOSED_DIMINUENDO
};

void compileAudioFromScript(lb_Audio* audio, char* script);
int validateScript(char* script);
void allocateMemory(lb_Audio* audio, char* script);
void buildAudioData(lb_Audio* audio, char* script);
void tuneByKeySignature(lb_Audio* audio, char* noteChar);
void assignFrequencyFromNoteChar(lb_Note note, char noteChar);
void tuneByAccidental(lb_Note note, char noteChar);
void assignDurationValue(lb_Audio* audio, char* script);

#endif /*Compiler_h*/