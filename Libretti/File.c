#include "include/File.h"
#include <stdio.h>
#include <stdlib.h>

char* loadScriptFile(char* filename)
{
	FILE* inputFile = fopen(filename, "rb");
	unsigned int filesize;

	fseek(inputFile, 0, SEEK_END);
	filesize = ftell(inputFile);
	rewind(inputFile);
	char* script = calloc(filesize, sizeof script);
	if (script != NULL)
		fread(script, sizeof script, filesize, inputFile);
	fclose(inputFile);
	return script;
}