#include "include/ScriptValidator.h"
#include "include/Constants.h"
#include "include/Strings.h"
#include "include/File.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateScript(char* script)
{
	int validationStatuses = ALL_OK;
	int readPosition = 0;
	int trackScopeCount = 0;
	int unclosedHeaders = 0;
	int unclosedTrackScopes = 0;
	unsigned char timeSigLower = 0;
	unsigned char timeSigUpper = 0;
	unsigned int totalBeats = 0;
	unsigned int totalBars = 0;
	unsigned int previousBarCount = 0;
	unsigned int currentBarCount = 0;
	unsigned char octave = 0;
	unsigned char tempo = 0;
	unsigned char parseState = READING_NOTHING;
	unsigned char previousParseState = 0;

	unsigned char tupletIsUnclosed = 0;
	unsigned char slurIsUnclosed = 0;

	unsigned char isReadingCrescendo = 0;
	unsigned char isReadingDiminuendo = 0;
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
				parseState = READING_NOTES;
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
					isReadingCrescendo = 1;
				}
				else
				{
					if (unclosedCrescendos > 0)
						unclosedCrescendos--;
					else
						unclosedCrescendos++;
					isReadingCrescendo = 0;
				}
				break;
			case '>':
				if (!isReadingDiminuendo)
				{
					isReadingDiminuendo = 1;
				}
				else
				{
					if (unclosedDiminuendos > 0)
						unclosedDiminuendos--;
					else
						unclosedDiminuendos++;
					isReadingDiminuendo = 0;
				}
				break;
			case ' ':
				if (isReadingCrescendo)
					isReadingCrescendo = 0;

				if (isReadingDiminuendo)
					isReadingDiminuendo = 0;

				if (parseState == IGNORING_FIRST_SPACE_IN_VALUE)
					parseState = READING_VALUE;
				else if (parseState == READING_HEADER)
					append(&header, script[readPosition]);
				else if (parseState == READING_VALUE)
					append(&value, script[readPosition]);
				break;
			case '|':
				totalBars++;
				currentBarCount++;
				break;
			case ':':
				parseState = IGNORING_FIRST_SPACE_IN_VALUE;
				if (strcmp(header.data, "name") != 0 &&
					strcmp(header.data, "author") != 0 &&
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

					//freeString(&upper);
					//freeString(&lower);
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
						strcmp(value.data, "pulse 10") != 0 &&
						strcmp(value.data, "pulse 25") != 0 &&
						strcmp(value.data, "noise") != 0 &&
						strcmp(value.data, "metallic") != 0)
					{
						lb_String filename = newString("Samples/");
						lb_String extension = newString(".bin");
						strcat(filename.data, value.data);
						strcat(filename.data, extension.data);
						if (!exists(filename.data))
						{
							validationStatuses |= INVALID_TIMBRE;
						}
						//freeString(&filename);
						//freeString(&extension);
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
				else if (parseState == READING_NOTES)
				{
					char substring[1];
					substring[0] = script[readPosition];
					if (substring[0] >= '1' && substring[0] <= '9')
						totalBeats += atoi(substring);
				}
				else if (parseState == IGNORING_FIRST_SPACE_IN_VALUE)
				{
					validationStatuses |= EXPECTED_SPACE_BETWEEN_HEADER_AND_VALUE;
				}
			}
		}

		if (parseState == READING_NOTHING ||
			parseState == READING_NOTES)
		{
			clear(&header);
			clear(&value);
		}

		readPosition++;
	} while (script[readPosition] != NULL);

	if (timeSigUpper > 0 && totalBars > 0)
		if ((totalBeats / totalBars) > timeSigUpper)
			validationStatuses |= BEATS_DO_NOT_MATCH_TIME_SIG;

	if (timeSigLower == 0 || timeSigUpper == 0)
		validationStatuses |= INVALID_TIME_SIG_PROVIDED;

	if (trackScopeCount > MAX_TRACKS)
		validationStatuses |= TRACK_SCOPE_COUNT_EXCEEDS_MAXIMUM;
	else if (trackScopeCount < 1)
		validationStatuses |= NO_TRACK_SCOPE_DETECTED;

	if (unclosedTrackScopes > 0)
		validationStatuses |= UNCLOSED_TRACK_SCOPE;

	if (unclosedHeaders > 0)
		validationStatuses |= UNCLOSED_HEADER_TAG;

	printCompilationStatuses(validationStatuses);

	//freeString(&header);
	//freeString(&value);
	//freeString(&debug);

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
	}
}