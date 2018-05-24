/**
*                      This file is part of:
*                          Libretti
*
* Script Validator
*
* Ensures the Libretti script file is valid according to the
* language specification before it is compiled.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef ScriptValidator_h
#define ScriptValidator_h

enum validationStatuses
{
	ALL_OK											= 0,
	NO_TRACK_SCOPE_DETECTED							= 1,
	INVALID_TIME_SIG_PROVIDED						= 1 << 1,
	INVALID_KEY_SIG_PROVIDED						= 1 << 2,
	INVALID_TEMPO_PROVIDED							= 1 << 3,
	INVALID_LOOP_VALUE								= 1 << 4,
	INVALID_DYNAMICS_VALUE							= 1 << 5,
	INVALID_PANNING_VALUE							= 1 << 6,
	INVALID_TIMBRE									= 1 << 7,
	UNCLOSED_TRACK_SCOPE							= 1 << 8,
	UNEXPECTED_HEADER_NAME							= 1 << 9,
	UNEXPECTED_HEADER_VALUE							= 1 << 10,
	INVALID_USE_OF_SYMBOL							= 1 << 11,
	BEATS_DO_NOT_MATCH_TIME_SIG						= 1 << 12,
	BAR_COUNTS_DO_NOT_MATCH							= 1 << 13,
	OCTAVE_SHIFTS_OUT_OF_RANGE						= 1 << 14,
	TRACK_SCOPE_COUNT_EXCEEDS_MAXIMUM				= 1 << 15,
	EXPECTED_SPACE_BETWEEN_HEADER_AND_VALUE			= 1 << 16,
	UNCLOSED_HEADER_TAG								= 1 << 17,
	UNCLOSED_TUPLET									= 1 << 18,
	UNCLOSED_SLUR									= 1 << 19,
	UNCLOSED_CRESCENDO								= 1 << 20,
	UNCLOSED_DIMINUENDO								= 1 << 21,
	EXTRA_HEADER_TAG_CLOSED_BRACKET					= 1 << 22,
	EXTRA_TRACK_SCOPE_CLOSED_BRACKET				= 1 << 23	
};

enum parseStates
{
	READING_NOTHING,
	READING_HEADER,
	IGNORING_FIRST_SPACE_IN_VALUE,
	READING_VALUE,
	READING_TRACK_SCOPE,
	READING_NOTE_FREQUENCY,
	READING_NOTE_ACCIDENTAL,
	READING_NOTE_DURATION
};

int validateScript(char* script);
unsigned char validateSymbol(char symbol, unsigned char parseState);
void printCompilationStatuses(int validationStatuses);

#endif /*ScriptValidator_h*/