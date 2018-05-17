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

enum compilationStatuses
{
	ALL_OK,
	NO_TRACK_SCOPE_DETECTED,
	NO_TIME_SIG_PROVIDED,
	UNCLOSED_TRACK_SCOPE,
	UNEXPECTED_HEADER_NAME,
	UNEXPECTED_HEADER_VALUE,
	INVALID_USE_OF_SYMBOL,
	BEATS_DO_NOT_MATCH_TIME_SIG,
	BAR_COUNTS_DO_NOT_MATCH,
	OCTAVE_SHIFTS_OUT_OF_RANGE,
	TRACK_SCOPE_COUNT_EXCEEDS_MAXIMUM,
	EXPECTED_SPACE_BETWEEN_HEADER_AND_VALUE,
	UNCLOSED_HEADER_TAG,
	UNCLOSED_TUPLET,
	UNCLOSED_SLUR,
	UNCLOSED_CRESCENDO,
	UNCLOSED_DIMINUENDO
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