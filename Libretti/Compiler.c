#include "include/Compiler.h"
#include "include/ScriptValidator.h"

void compileAudioFromScript(lb_Audio* audio, char* script)
{
	if (validateScript(script) == ALL_OK)
	{

	}
	else
	{
		printf("\nCompilation Failed.");
	}
}

void allocateMemory(lb_Audio* audio, char* script)
{

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