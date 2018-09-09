#include "include/Compiler.h"
#include "include/ScriptParseStates.h"
#include "include/ScriptValidator.h"
#include "include/Strings.h"
#include "include/Timing.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void compileAudioFromScript(lb_Audio* audio, char* script)
{
	if (validateScript(script) == ALL_OK)
	{
		allocateMemory(audio, script);
		buildAudioData(audio, script);
	}
	else
	{
		printf("\nCompilation Failed.");
	}
}

void allocateMemory(lb_Audio* audio, char* script)
{
	int readPosition = 0;
	int currentTrack = -1;
	int noteCount = 0;
	int tempoEventCount = 0;
	int lyricsEventCount = 0;
	char symbol = NULL;
	bool isReadingHeader = false;
	bool isReadingValue = false;
	lb_String header = newString("");

	do
	{
		symbol = script[readPosition];

		switch (symbol)
		{
		case '{':
			currentTrack++;
			noteCount = 0;
			break;
		case '[':
			isReadingHeader = true;
			break;
		case ':':
			if (strcmp(header.data, "tempo") == 0)
				tempoEventCount++;
			else if (strcmp(header.data, "lyric") == 0)
				lyricsEventCount++;
			isReadingHeader = false;
			isReadingValue = true;
			clear(&header);
			break;
		case '}':
			audio->tracks[currentTrack].noteEvents = malloc(sizeof(lb_NoteEvent) * noteCount);
			audio->tracks[currentTrack].noteCount = noteCount;
			break;
		case ']':
			isReadingValue = false;
			break;
		default:
			if (!isReadingValue)
			{
				if (isReadingHeader)
					append(&header, symbol);
				else if (symbol >= 'A' && symbol <= 'G' ||
					symbol == 'R')
					noteCount++;
			}
		}
		readPosition++;
	} while (symbol != NULL);

	audio->tempoEvents = malloc(sizeof(lb_TempoEvent) * tempoEventCount);
	audio->tempoEventCount = tempoEventCount;
	audio->lyricsEvents = malloc(sizeof(lb_LyricsEvent) * lyricsEventCount);
	audio->lyricsEventCount = lyricsEventCount;
	audio->trackCount = currentTrack + 1;
	freeString(&header);
}

void buildAudioData(lb_Audio* audio, char* script)
{
	int readPosition = 0;
	int currentNote = 0;
	int currentTrack = 0;
	int currentTempoEvent = 0;
	int currentLyricsEvent = 0;

	double currentTime = 0.0;

	uint8_t timeSigLower = 0;
	uint8_t timeSigUpper = 0;
	uint8_t octave = 0;
	uint8_t tempo = 0;
	uint8_t dynamic = 0;
	uint8_t panning = 0;
	uint8_t timbre = 0;
	bool tupletIsOpened = false;
	bool slurIsOpened = false;
	bool isReadingCrescendo = false;
	bool isReadingDiminuendo = false;

	uint8_t parseState = READING_NOTHING;
	uint8_t previousParseState = 0;
	lb_String header = newString("");
	lb_String value = newString("");

	do
	{
		switch (script[readPosition])
		{
		case '{':
			parseState = READING_TRACK_SCOPE;
			break;
		case '[':
			previousParseState = parseState;
			parseState = READING_HEADER;
			break;
		case '_':
			tupletIsOpened = !tupletIsOpened;
			break;
		case '~':
			slurIsOpened = !slurIsOpened;
			break;
		case '<':
			isReadingCrescendo = !isReadingCrescendo;
			break;
		case '>':
			isReadingDiminuendo = !isReadingDiminuendo;
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
		case ':':
			parseState = IGNORING_FIRST_SPACE_IN_VALUE;
			break;
		case ']':
			if (strcmp(header.data, "name") == 0)
			{
				int valueReadPosition = 0;
				while (value.data[valueReadPosition] != 0)
				{
					audio->name[valueReadPosition] = value.data[valueReadPosition];
					valueReadPosition++;
				}
			}
			else if (strcmp(header.data, "artist") == 0)
			{
				int valueReadPosition = 0;
				while (value.data[valueReadPosition] != 0)
				{
					audio->artist[valueReadPosition] = value.data[valueReadPosition];
					valueReadPosition++;
				}
			}
			else if (strcmp(header.data, "key sig") == 0)
			{
				if (strcmp(value.data, "C major") != 0)
					audio->keySignature = C_MAJOR;
				else if (strcmp(value.data, "G major") != 0)
					audio->keySignature = G_MAJOR;
				else if (strcmp(value.data, "D major") != 0)
					audio->keySignature = D_MAJOR;
				else if (strcmp(value.data, "A major") != 0)
					audio->keySignature = A_MAJOR;
				else if (strcmp(value.data, "E major") != 0)
					audio->keySignature = E_MAJOR;
				else if (strcmp(value.data, "B major") != 0)
					audio->keySignature = B_MAJOR;
				else if (strcmp(value.data, "Fs major") != 0)
					audio->keySignature = Fs_MAJOR;
				else if (strcmp(value.data, "Gb major") != 0)
					audio->keySignature = Gb_MAJOR;
				else if (strcmp(value.data, "Db major") != 0)
					audio->keySignature = Db_MAJOR;
				else if (strcmp(value.data, "Ab major") != 0)
					audio->keySignature = Ab_MAJOR;
				else if (strcmp(value.data, "Eb major") != 0)
					audio->keySignature = Eb_MAJOR;
				else if (strcmp(value.data, "Bb major") != 0)
					audio->keySignature = Bb_MAJOR;
				else if (strcmp(value.data, "F major") != 0)
					audio->keySignature = F_MAJOR;
				else if (strcmp(value.data, "A minor") != 0)
					audio->keySignature = A_MINOR;
				else if (strcmp(value.data, "E minor") != 0)
					audio->keySignature = E_MINOR;
				else if (strcmp(value.data, "B minor") != 0)
					audio->keySignature = B_MINOR;
				else if (strcmp(value.data, "Fs minor") != 0)
					audio->keySignature = Fs_MINOR;
				else if (strcmp(value.data, "Cs minor") != 0)
					audio->keySignature = Cs_MINOR;
				else if (strcmp(value.data, "Gs minor") != 0)
					audio->keySignature = Gs_MINOR;
				else if (strcmp(value.data, "Ds minor") != 0)
					audio->keySignature = Ds_MINOR;
				else if (strcmp(value.data, "Eb minor") != 0)
					audio->keySignature = Eb_MINOR;
				else if (strcmp(value.data, "Bb minor") != 0)
					audio->keySignature = Bb_MINOR;
				else if (strcmp(value.data, "F minor") != 0)
					audio->keySignature = F_MINOR;
				else if (strcmp(value.data, "C minor") != 0)
					audio->keySignature = C_MINOR;
				else if (strcmp(value.data, "G minor") != 0)
					audio->keySignature = G_MINOR;
				else if (strcmp(value.data, "D minor") != 0)
					audio->keySignature = D_MINOR;
			}
			else if (strcmp(header.data, "time sig") == 0)
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

				audio->timeSignature[0] = timeSigUpper;
				audio->timeSignature[1] = timeSigLower;

				//freeString(&upper);
				//freeString(&lower);
			}
			else if (strcmp(header.data, "tempo") == 0)
			{
				tempo = atoi(value.data);
				if (tempo == 0)
				{
					if (strcmp(value.data, "largo") != 0)
						tempo = LARGO;
					else if (strcmp(value.data, "adagio") != 0)
						tempo = ADAGIO;
					else if (strcmp(value.data, "adante") != 0)
						tempo = ADANTE;
					else if (strcmp(value.data, "moderato") != 0)
						tempo = MODERATO;
					else if (strcmp(value.data, "allegro") != 0)
						tempo = ALLEGRO;
					else if (strcmp(value.data, "presto") != 0)
						tempo = PRESTO;
				}
				audio->tempoEvents[currentTempoEvent].tempo = tempo;
				audio->tempoEvents[currentTempoEvent].startTime = currentTime;
			}
			else if (strcmp(header.data, "dynamic") == 0)
			{
				if (strcmp(value.data, "ppp") != 0)
					dynamic = PPP;
				else if (strcmp(value.data, "pp") != 0)
					dynamic = PP;
				else if (strcmp(value.data, "p") != 0)
					dynamic = P;
				else if (strcmp(value.data, "mp") != 0)
					dynamic = MP;
				else if (strcmp(value.data, "mf") != 0)
					dynamic = MF;
				else if (strcmp(value.data, "f") != 0)
					dynamic = F;
				else if (strcmp(value.data, "ff") != 0)
					dynamic = FF;
				else if (strcmp(value.data, "fff") != 0)
					dynamic = FFF;
			}
			else if (strcmp(header.data, "reverb") == 0)
			{

			}
			else if (strcmp(header.data, "vibrato") == 0)
			{

			}
			else if (strcmp(header.data, "panning") == 0)
			{
				float panningValue = atof(value.data);
				if (panningValue == 0)
				{
					if (strcmp(value.data, "far left") != 0)
						panning = REAR_LEFT;
					else if (strcmp(value.data, "left") != 0)
						panning = FRONT_LEFT;
					else if (strcmp(value.data, "mono") != 0)
						panning = CENTRE;
					else if (strcmp(value.data, "right") != 0)
						panning = FRONT_RIGHT;
					else if (strcmp(value.data, "far right") != 0)
						panning = REAR_RIGHT;
				}
				else
				{
					panning = (panningValue + 1.0) * 127;
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
					lb_String filename = newString("Samples/");
					lb_String extension = newString(".pcm");
					strcat(filename.data, value.data);
					strcat(filename.data, extension.data);
					if (!exists(filename.data))
					{

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

					}
				}
			}
			else if (strcmp(header.data, "octave") == 0)
			{
				octave = atoi(value.data);
			}
			parseState = previousParseState;
			break;
		case '}':
			parseState = READING_NOTHING;
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
					if (tupletIsOpened)
						durationValue = (durationValue * 2) / 3;

				}
			}
			else if (parseState == READING_NOTE_ACCIDENTAL)
			{
				if (script[readPosition] >= '1' && script[readPosition] <= '9')
					parseState = READING_NOTE_DURATION;
			}
		}
		readPosition++;
	} while (script[readPosition] != NULL);
}

void tuneByKeySignature(lb_Audio* audio, char* noteChar)
{

}

void assignFrequencyFromNoteChar(lb_Note note, char noteChar)
{

}

void tuneByAccidental(lb_Note note, char noteChar)
{

}

void assignDurationValue(lb_Audio* audio, char* script)
{

}