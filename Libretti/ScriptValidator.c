#include "include/ScriptValidator.h"
#include "include/Constants.h"
#include <stdio.h>
#include <string.h>

int validateScript(char* script)
{
	int validationStatuses = ALL_OK;
	int readPosition = 0;
	unsigned char trackScopeCount = 0;
	unsigned char unclosedHeaders = 0;
	unsigned char unclosedTrackScopes = 0;
	unsigned char timeSigLower = 0;
	unsigned char timeSigUpper = 0;
	unsigned int totalBeats = 0;
	unsigned int totalBars = 0;
	unsigned int previousBarCount = 0;
	unsigned int currentBarCount = 0;
	unsigned char octave = 0;
	unsigned char parseState = READING_NOTHING;
	unsigned char previousParseState = 0;
	char header[16] = "";
	char value[16] = "";

	do
	{
		if (!validateSymbol(script[readPosition], parseState))
		{
			validationStatuses |= INVALID_USE_OF_SYMBOL;
		}
		else
		{
			if (parseState == IGNORING_FIRST_SPACE_IN_VALUE)
				if (script[readPosition] != ' ')
					parseState = READING_VALUE;

			switch (script[readPosition])
			{
			case '{': 
				parseState = READING_NOTES;
				trackScopeCount++;
				unclosedTrackScopes++;
				break;
			case '[':
				previousParseState = parseState;
				parseState = READING_HEADER;
				unclosedHeaders++;
				break;
			case ':':
				parseState = IGNORING_FIRST_SPACE_IN_VALUE;
				if (header != "name" ||
					header != "author" ||
					header != "lyric" ||
					header != "time sig" ||
					header != "key sig" ||
					header != "tempo" ||
					header != "timbre" ||
					header != "octave" ||
					header != "dynamic" ||
					header != "loop" ||
					header != "segment" ||
					header != "end" ||
					header != "cue" ||
					header != "panning" ||
					header != "reverb" ||
					header != "echo" ||
					header != "eq" ||
					header != "vibrato" ||
					header != "flanging" ||
					header != "crossfading" ||
					header != "pitch blend")
					validationStatuses |= UNEXPECTED_HEADER_NAME;
				break;
			case ']':
				parseState = previousParseState;
				unclosedHeaders--;
				break;
			case '}':
				parseState = READING_NOTHING;
				unclosedTrackScopes--;
				if (octave < 1 || octave > 7)
					validationStatuses |= OCTAVE_SHIFTS_OUT_OF_RANGE;
				break;

				readPosition++;
			}
		}

		if (parseState == READING_HEADER)
		{
			
		}
		else if (parseState == READING_VALUE)
		{
			
		}
		else if (parseState == READING_NOTHING ||
			parseState == READING_NOTES)
		{
			header[0] = NULL;
			value[0] = NULL;
		}

		readPosition++;
	} while (script[readPosition] != NULL);

	if (timeSigLower == 0 || timeSigUpper == 0)
		validationStatuses |= NO_TIME_SIG_PROVIDED;

	if (trackScopeCount > MAX_TRACKS)
		validationStatuses |= TRACK_SCOPE_COUNT_EXCEEDS_MAXIMUM;
	else if (trackScopeCount < 1)
		validationStatuses |= NO_TRACK_SCOPE_DETECTED;

	if (unclosedTrackScopes > 0)
		validationStatuses |= UNCLOSED_TRACK_SCOPE;

	if (unclosedHeaders > 0)
		validationStatuses |= UNCLOSED_HEADER_TAG;

	printCompilationStatuses(validationStatuses);

	return validationStatuses;
}

unsigned char validateSymbol(char symbol, unsigned char parseState)
{
	unsigned char valid = 0;

	if (parseState == READING_NOTHING)
	{
		if (symbol == '[' || symbol == '{' ||
			symbol == ' ' || symbol == '\n' || 
			symbol == '\r')
			valid = 1;
	}
	else if (parseState == READING_NOTES)
	{

		if ((symbol >= 'A' && symbol <= 'G') ||
			(symbol >= '1' && symbol <= '9'))
		{
			valid = 1;
		}
		else
		{
			switch (symbol)
			{
				case '[':
				case ' ':
				case '\n':
				case '\r':
				case '#': case 'b':	case 'n':
				case '|':
				case '*':
				case '.':
				case '~':
				case '+':
				case '-':
				case '_':
				case '<':
				case '>':
				case 'R':
				case '}':
					valid = 1;
			}
		}
	}
	else
	{
		valid = 1;
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
		if (validationStatuses & NO_TIME_SIG_PROVIDED)
			printf("Code %d: \tNO_TIME_SIG_PROVIDED.\n", NO_TIME_SIG_PROVIDED);
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
	}
}