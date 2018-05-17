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
	NO_TRACK_SCOPE_DETECTED							= 1 << 0,
	NO_TIME_SIG_PROVIDED							= 1 << 1,
	UNCLOSED_TRACK_SCOPE							= 1 << 2,
	UNEXPECTED_HEADER_NAME							= 1 << 3,
	UNEXPECTED_HEADER_VALUE							= 1 << 4,
	INVALID_USE_OF_SYMBOL							= 1 << 5,
	BEATS_DO_NOT_MATCH_TIME_SIG						= 1 << 6,
	BAR_COUNTS_DO_NOT_MATCH							= 1 << 7,
	OCTAVE_SHIFTS_OUT_OF_RANGE						= 1 << 8,
	TRACK_SCOPE_COUNT_EXCEEDS_MAXIMUM				= 1 << 9,
	EXPECTED_SPACE_BETWEEN_HEADER_AND_VALUE			= 1 << 10,
	UNCLOSED_HEADER_TAG								= 1 << 11,
	UNCLOSED_TUPLET									= 1 << 12,
	UNCLOSED_SLUR									= 1 << 13,
	UNCLOSED_CRESCENDO								= 1 << 14,
	UNCLOSED_DIMINUENDO								= 1 << 15
};

enum parseStates
{
	READING_NOTHING,
	READING_HEADER,
	IGNORING_FIRST_SPACE_IN_VALUE,
	READING_VALUE,
	READING_NOTES
};

int validateScript(char* script);
unsigned char validateSymbol(char symbol, unsigned char parseState);
void printCompilationStatuses(int validationStatuses);

#endif /*ScriptValidator_h*/