#include "include/Compiler.h"
#include "include/ScriptValidator.h"
#include "include/Strings.h"
#include <stdlib.h>
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