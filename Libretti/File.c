#include "include/File.h"
#include <stdio.h>
#include <stdlib.h>

bool exists(char* filename)
{
	FILE* inputFile = fopen(filename, "rb");
	if (inputFile != NULL)
		fclose(inputFile);
	return (bool)inputFile;
}

char* loadScriptFromFile(char* filename)
{
	FILE* inputFile = fopen(filename, "rb");
	char* script = 0;
	if (inputFile != NULL)
	{
		fseek(inputFile, 0, SEEK_END);
		unsigned int filesize = ftell(inputFile);
		rewind(inputFile);
		script = malloc(sizeof *script * (filesize + 1));
		if (script != NULL)
		{
			fread(script, sizeof *script, filesize, inputFile);
			script[filesize] = NULL;
		}
		fclose(inputFile);
	}
	return script;
}