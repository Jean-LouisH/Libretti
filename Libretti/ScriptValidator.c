#include "include/ScriptValidator.h"
#include "include/Constants.h"
#include "include/Strings.h"
#include "include/File.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int validateScript(char* script)
{
	int validationStatuses = ALL_OK;
	int readPosition = 0;
	int trackScopeCount = 0;
	int unclosedHeaders = 0;
	int unclosedTrackScopes = 0;
	uint8_t timeSigLower = 0;
	uint8_t timeSigUpper = 0;
	double beatsInABar = 0;
	unsigned int previousBarCount = 0;
	unsigned int currentBarCount = 0;
	uint8_t octave = 0;
	uint8_t tempo = 0;
	uint8_t parseState = READING_NOTHING;
	uint8_t previousParseState = 0;

	bool tupletIsUnclosed = false;
	bool slurIsUnclosed = false;

	bool isReadingCrescendo = false;
	bool isReadingDiminuendo = false;
	int unclosedCrescendos = 0;
	int unclosedDiminuendos = 0;

	lb_String header = newString("");
	lb_String value = newString("");
	lb_String debug = newString("");

	do
	{
		append(&debug, script[readPosition]);
		if (!validateSymbol(script[readPosition], parseState))
		{
			validationStatuses |= INVALID_USE_OF_SYMBOL;
		}
		else
		{
			switch (script[readPosition])
			{
			case '{':
				parseState = READING_TRACK_SCOPE;
				trackScopeCount++;
				unclosedTrackScopes++;
				break;
			case '[':
				previousParseState = parseState;
				parseState = READING_HEADER;
				unclosedHeaders++;
				break;
			case '_':
				tupletIsUnclosed = !tupletIsUnclosed;
				break;
			case '~':
				slurIsUnclosed = !slurIsUnclosed;
				break;
			case '<':
				if (!isReadingCrescendo)
				{
					isReadingCrescendo = true;
				}
				else
				{
					if (unclosedCrescendos > 0)
						unclosedCrescendos--;
					else
						unclosedCrescendos++;
					isReadingCrescendo = false;
				}
				break;
			case '>':
				if (!isReadingDiminuendo)
				{
					isReadingDiminuendo = true;
				}
				else
				{
					if (unclosedDiminuendos > 0)
						unclosedDiminuendos--;
					else
						unclosedDiminuendos++;
					isReadingDiminuendo = false;
				}
				break;
			case ' ':
				if (isReadingCrescendo)
					isReadingCrescendo = false;

				if (isReadingDiminuendo)
					isReadingDiminuendo = false;

				if (parseState == IGNORING_FIRST_SPACE_IN_VALUE)
					parseState = READING_VALUE;
				else if (parseState == READING_HEADER)
					append(&header, script[readPosition]);
				else if (parseState == READING_VALUE)
					append(&value, script[readPosition]);
				else if (parseState == READING_NOTE_DURATION)
					parseState = READING_TRACK_SCOPE;
				break;
			case '|':
				if (beatsInABar != 0)
					if (round(beatsInABar) != timeSigUpper)
							validationStatuses |= BEATS_DO_NOT_MATCH_TIME_SIG;
				beatsInABar = 0;
				currentBarCount++;
				break;
			case ':':
				parseState = IGNORING_FIRST_SPACE_IN_VALUE;
				if (strcmp(header.data, "name") != 0 &&
					strcmp(header.data, "artist") != 0 &&
					strcmp(header.data, "lyric") != 0 &&
					strcmp(header.data, "time sig") != 0 &&
					strcmp(header.data, "key sig") != 0 &&
					strcmp(header.data, "tempo") != 0 &&
					strcmp(header.data, "timbre") != 0 &&
					strcmp(header.data, "octave") != 0 &&
					strcmp(header.data, "dynamic") != 0 &&
					strcmp(header.data, "loop") != 0 &&
					strcmp(header.data, "segment") != 0 &&
					strcmp(header.data, "end") != 0 &&
					strcmp(header.data, "cue") != 0 &&
					strcmp(header.data, "panning") != 0 &&
					strcmp(header.data, "reverb") != 0 &&
					strcmp(header.data, "echo") != 0 &&
					strcmp(header.data, "eq") != 0 &&
					strcmp(header.data, "vibrato") != 0 &&
					strcmp(header.data, "flanging") != 0 &&
					strcmp(header.data, "crossfading") != 0 &&
					strcmp(header.data, "pitch blend") != 0)
				{
					validationStatuses |= UNEXPECTED_HEADER_NAME;
				}
				break;
			case ']':
				if (strcmp(header.data, "time sig") == 0)
				{
					int valueReadPosition = 0;
					lb_String upper = newString("");
					lb_String lower = newString("");

					while (value.data[valueReadPosition] != 0 &&
						value.data[valueReadPosition] != '/')
					{
						append(&upper, value.data[valueReadPosition]);
						valueReadPosition++;
					}

					valueReadPosition++;

					while (value.data[valueReadPosition] != 0)
					{
						append(&lower, value.data[valueReadPosition]);
						valueReadPosition++;
					}

					timeSigUpper = atoi(upper.data);
					timeSigLower = atoi(lower.data);
				}
				else if (strcmp(header.data, "key sig") == 0)
				{

					if (strcmp(value.data, "C major") != 0 &&
						strcmp(value.data, "G major") != 0 &&
						strcmp(value.data, "D major") != 0 &&
						strcmp(value.data, "A major") != 0 &&
						strcmp(value.data, "E major") != 0 &&
						strcmp(value.data, "B major") != 0 &&
						strcmp(value.data, "Fs major") != 0 &&
						strcmp(value.data, "Gb major") != 0 &&
						strcmp(value.data, "Db major") != 0 &&
						strcmp(value.data, "Ab major") != 0 &&
						strcmp(value.data, "Eb major") != 0 &&
						strcmp(value.data, "Bb major") != 0 &&
						strcmp(value.data, "F major") != 0 &&
						strcmp(value.data, "A minor") != 0 &&
						strcmp(value.data, "E minor") != 0 &&
						strcmp(value.data, "B minor") != 0 &&
						strcmp(value.data, "Fs minor") != 0 &&
						strcmp(value.data, "Cs minor") != 0 &&
						strcmp(value.data, "Gs minor") != 0 &&
						strcmp(value.data, "Ds minor") != 0 &&
						strcmp(value.data, "Eb minor") != 0 &&
						strcmp(value.data, "Bb minor") != 0 &&
						strcmp(value.data, "F minor") != 0 &&
						strcmp(value.data, "C minor") != 0 &&
						strcmp(value.data, "G minor") != 0 &&
						strcmp(value.data, "D minor") != 0)
					{
						validationStatuses |= INVALID_KEY_SIG_PROVIDED;
					}
				}
				else if (strcmp(header.data, "tempo") == 0)
				{
					tempo = atoi(value.data);
					if (tempo == 0)
					{
						if (strcmp(value.data, "largo") != 0 &&
							strcmp(value.data, "adagio") != 0 &&
							strcmp(value.data, "adante") != 0 &&
							strcmp(value.data, "moderato") != 0 &&
							strcmp(value.data, "allegro") != 0 &&
							strcmp(value.data, "presto") != 0)
						{
							validationStatuses |= INVALID_TEMPO_PROVIDED;
						}
					}
				}
				else if (strcmp(header.data, "timbre") == 0)
				{
					if (strcmp(value.data, "square wave") != 0 &&
						strcmp(value.data, "sine wave") != 0 &&
						strcmp(value.data, "triangle wave") != 0 &&
						strcmp(value.data, "sawtooth wave") != 0 &&
						strcmp(value.data, "pulse 10") != 0 &&
						strcmp(value.data, "pulse 25") != 0 &&
						strcmp(value.data, "noise") != 0 &&
						strcmp(value.data, "metallic") != 0)
					{
#ifdef _DEBUG
						lb_String filename = newString("../Libretti/Samples/");
#else
						lb_String filename = newString("Samples/");
#endif
						lb_String extension = newString(".pcm");
						strcat(filename.data, value.data);
						strcat(filename.data, extension.data);
						if (!exists(filename.data))
						{
							validationStatuses |= INVALID_TIMBRE;
						}
					}
				}
				else if (strcmp(header.data, "loop") == 0)
				{
					int loops = atoi(value.data);
					if (loops == 0)
					{
						if (strcmp(value.data, "none") != 0 &&
							strcmp(value.data, "infinity") != 0)
						{
							validationStatuses |= INVALID_LOOP_VALUE;
						}
					}
				}
				else if (strcmp(header.data, "dynamic") == 0)
				{
					if (strcmp(value.data, "ppp") != 0 &&
						strcmp(value.data, "pp") != 0 &&
						strcmp(value.data, "p") != 0 &&
						strcmp(value.data, "mp") != 0 &&
						strcmp(value.data, "mf") != 0 &&
						strcmp(value.data, "f") != 0 &&
						strcmp(value.data, "ff") != 0 &&
						strcmp(value.data, "fff") != 0)
					{
						validationStatuses |= INVALID_DYNAMICS_VALUE;
					}
				}
				else if (strcmp(header.data, "octave") == 0)
				{
					octave = atoi(value.data);
				}
				else if (strcmp(header.data, "panning") == 0)
				{
					float panning = atof(value.data);
					if (panning == 0)
					{
						if (strcmp(value.data, "far left") != 0 &&
							strcmp(value.data, "left") != 0 &&
							strcmp(value.data, "mono") != 0 &&
							strcmp(value.data, "right") != 0 &&
							strcmp(value.data, "far right") != 0)
						{
							validationStatuses |= INVALID_PANNING_VALUE;
						}
					}
					else if (panning < -1.0 && panning > 1.0)
					{
						validationStatuses |= INVALID_PANNING_VALUE;
					}
				}
				parseState = previousParseState;
				unclosedHeaders--;
				break;
			case '}':
				parseState = READING_NOTHING;
				unclosedTrackScopes--;
				if (octave < 1 || octave > 7)
					validationStatuses |= OCTAVE_SHIFTS_OUT_OF_RANGE;

				if (previousBarCount != 0)
					if (currentBarCount != previousBarCount)
						validationStatuses |= BAR_COUNTS_DO_NOT_MATCH;

				previousBarCount = currentBarCount;
				currentBarCount = 0;
				break;
			case '+':
				octave++;
				break;
			case '-':
				octave--;
				break;
			default:
				if (parseState == READING_HEADER)
				{
					append(&header, script[readPosition]);
				}
				else if (parseState == READING_VALUE)
				{
					append(&value, script[readPosition]);
				}
				else if (parseState == IGNORING_FIRST_SPACE_IN_VALUE)
				{
					validationStatuses |= EXPECTED_SPACE_BETWEEN_HEADER_AND_VALUE;
				}
				else if (parseState == READING_TRACK_SCOPE)
				{
					if ((script[readPosition] >= 'A' && script[readPosition] <= 'G') ||
						script[readPosition] == 'R')
						parseState = READING_NOTE_FREQUENCY;
				}
				else if (parseState == READING_NOTE_FREQUENCY)
				{
					if (script[readPosition] == '#' || script[readPosition] == 'b' ||
						script[readPosition] == 'n')
					{
						parseState = READING_NOTE_ACCIDENTAL;
					}
					else if (script[readPosition] >= '1' && script[readPosition] <= '9')
					{
						parseState = READING_NOTE_DURATION;
						char substring[1];
						substring[0] = script[readPosition];
						double durationValue = atoi(substring);
						if (tupletIsUnclosed)
							durationValue = (durationValue * 2) / 3;
						beatsInABar += durationValue;
					}
				}
				else if (parseState == READING_NOTE_ACCIDENTAL)
				{
					if (script[readPosition] >= '1' && script[readPosition] <= '9')
						parseState = READING_NOTE_DURATION;
				}
			}
		}

		if (parseState == READING_NOTHING ||
			parseState == READING_TRACK_SCOPE)
		{
			clear(&header);
			clear(&value);
		}

		readPosition++;
	} while (script[readPosition] != NULL);

	if (timeSigLower == 0 || timeSigUpper == 0)
		validationStatuses |= INVALID_TIME_SIG_PROVIDED;

	if (trackScopeCount > MAX_TRACKS)
		validationStatuses |= TRACK_SCOPE_COUNT_EXCEEDS_MAXIMUM;
	else if (trackScopeCount < 1)
		validationStatuses |= NO_TRACK_SCOPE_DETECTED;

	if (unclosedTrackScopes > 0)
		validationStatuses |= UNCLOSED_TRACK_SCOPE;
	else if (unclosedTrackScopes < 0)
		validationStatuses |= EXTRA_TRACK_SCOPE_CLOSED_BRACKET;

	if (unclosedHeaders > 0)
		validationStatuses |= UNCLOSED_HEADER_TAG;
	else if (unclosedHeaders < 0)
		validationStatuses |= EXTRA_HEADER_TAG_CLOSED_BRACKET;

	printCompilationStatuses(validationStatuses);

	//freeString(&header);
	//freeString(&value);
	//freeString(&debug);

	return validationStatuses;
}

bool validateSymbol(char symbol, uint8_t parseState)
{
	bool valid = false;

	if (parseState == READING_NOTHING)
	{
		if (symbol == '[' || symbol == '{' ||
			symbol == ' ' || symbol == '\n' ||
			symbol == '\r')
			valid = true;
	}
	else if (parseState == READING_TRACK_SCOPE)
	{
		if (symbol >= 'A' && symbol <= 'G')
		{
			valid = true;
		}
		else
		{
			switch (symbol)
			{
			case '[':
			case ' ':
			case '\n':
			case '\r':
			case '|':
			case '~':
			case '+':
			case '-':
			case '_':
			case '<':
			case '>':
			case 'R':
			case '}':
				valid = true;
			}
		}
	}
	else if (parseState == READING_NOTE_FREQUENCY)
	{
		if (symbol >= '1' && symbol <= '9')
		{
			valid = true;
		}
		else
		{
			switch (symbol)
			{
			case '#': case 'b':	case 'n':
				valid = true;
			}
		}
	}
	else if (parseState == READING_NOTE_ACCIDENTAL)
	{
		if (symbol >= '1' && symbol <= '9')
			valid = true;
	}
	else if (parseState == READING_NOTE_DURATION)
	{
		if (symbol >= '0' && symbol <= '9')
		{
			valid = true;
		}
		else
		{
			switch (symbol)
			{
			case '*':
			case '.':
			case '>':
			case ' ':
				valid = true;
			}
		}
	}
	else
	{
		valid = true;
	}

	return valid;
}

void printCompilationStatuses(int validationStatuses)
{
	printf("\n\t\tLibretti Script Validation Statuses");
	printf("\n\n");

	if (validationStatuses == ALL_OK)
	{
		printf("Code %d: ALL_OK, Successfully passed validation.\n", ALL_OK);
	}
	else
	{
		if (validationStatuses & NO_TRACK_SCOPE_DETECTED)
			printf("Code %d: \tNO_TRACK_SCOPE_DETECTED.\n", NO_TRACK_SCOPE_DETECTED);
		if (validationStatuses & INVALID_TIME_SIG_PROVIDED)
			printf("Code %d: \tINVALID_TIME_SIG_PROVIDED.\n", INVALID_TIME_SIG_PROVIDED);
		if (validationStatuses & INVALID_KEY_SIG_PROVIDED)
			printf("Code %d: \tINVALID_KEY_SIG_PROVIDED.\n", INVALID_KEY_SIG_PROVIDED);
		if (validationStatuses & INVALID_TEMPO_PROVIDED)
			printf("Code %d: \tINVALID_TEMPO_PROVIDED.\n", INVALID_TEMPO_PROVIDED);
		if (validationStatuses & INVALID_LOOP_VALUE)
			printf("Code %d: \tINVALID_LOOP_VALUE.\n", INVALID_LOOP_VALUE);
		if (validationStatuses & INVALID_DYNAMICS_VALUE)
			printf("Code %d: \tINVALID_DYNAMICS_VALUE.\n", INVALID_DYNAMICS_VALUE);
		if (validationStatuses & INVALID_PANNING_VALUE)
			printf("Code %d: \tINVALID_PANNING_VALUE.\n", INVALID_PANNING_VALUE);
		if (validationStatuses & INVALID_TIMBRE)
			printf("Code %d: \tINVALID_TIMBRE.\n", INVALID_TIMBRE);
		if (validationStatuses & UNCLOSED_TRACK_SCOPE)
			printf("Code %d: \tUNCLOSED_TRACK_SCOPE.\n", UNCLOSED_TRACK_SCOPE);
		if (validationStatuses & UNEXPECTED_HEADER_NAME)
			printf("Code %d: \tUNEXPECTED_HEADER_NAME.\n", UNEXPECTED_HEADER_NAME);
		if (validationStatuses & UNEXPECTED_HEADER_VALUE)
			printf("Code %d: \tUNEXPECTED_HEADER_VALUE.\n", UNEXPECTED_HEADER_VALUE);
		if (validationStatuses & INVALID_USE_OF_SYMBOL)
			printf("Code %d: \tINVALID_USE_OF_SYMBOL.\n", INVALID_USE_OF_SYMBOL);
		if (validationStatuses & BEATS_DO_NOT_MATCH_TIME_SIG)
			printf("Code %d: \tBEATS_DO_NOT_MATCH_TIME_SIG.\n", BEATS_DO_NOT_MATCH_TIME_SIG);
		if (validationStatuses & BAR_COUNTS_DO_NOT_MATCH)
			printf("Code %d: \tBAR_COUNTS_DO_NOT_MATCH.\n", BAR_COUNTS_DO_NOT_MATCH);
		if (validationStatuses & OCTAVE_SHIFTS_OUT_OF_RANGE)
			printf("Code %d: \tOCTAVE_SHIFTS_OUT_OF_RANGE.\n", OCTAVE_SHIFTS_OUT_OF_RANGE);
		if (validationStatuses & TRACK_SCOPE_COUNT_EXCEEDS_MAXIMUM)
			printf("Code %d: \tTRACK_SCOPE_COUNT_EXCEEDS_MAXIMUM.\n", TRACK_SCOPE_COUNT_EXCEEDS_MAXIMUM);
		if (validationStatuses & EXPECTED_SPACE_BETWEEN_HEADER_AND_VALUE)
			printf("Code %d: \tEXPECTED_SPACE_BETWEEN_HEADER_AND_VALUE.\n", EXPECTED_SPACE_BETWEEN_HEADER_AND_VALUE);
		if (validationStatuses & UNCLOSED_HEADER_TAG)
			printf("Code %d: \tUNCLOSED_HEADER_TAG.\n", UNCLOSED_HEADER_TAG);
		if (validationStatuses & UNCLOSED_TUPLET)
			printf("Code %d: \tUNCLOSED_TUPLET.\n", UNCLOSED_TUPLET);
		if (validationStatuses & UNCLOSED_SLUR)
			printf("Code %d: \tUNCLOSED_SLUR.\n", UNCLOSED_SLUR);
		if (validationStatuses & UNCLOSED_CRESCENDO)
			printf("Code %d: \tUNCLOSED_CRESCENDO.\n", UNCLOSED_CRESCENDO);
		if (validationStatuses & UNCLOSED_DIMINUENDO)
			printf("Code %d: \tUNCLOSED_DIMINUENDO.\n", UNCLOSED_DIMINUENDO);
		if (validationStatuses & EXTRA_HEADER_TAG_CLOSED_BRACKET)
			printf("Code %d: \tEXTRA_HEADER_TAG_CLOSED_BRACKET.\n", EXTRA_HEADER_TAG_CLOSED_BRACKET);
		if (validationStatuses & EXTRA_TRACK_SCOPE_CLOSED_BRACKET)
			printf("Code %d: \tEXTRA_TRACK_SCOPE_CLOSED_BRACKET.\n", EXTRA_TRACK_SCOPE_CLOSED_BRACKET);
	}
}