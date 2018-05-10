#include "include/File.h"
#include <stdio.h>
#include <stdlib.h>

char* loadScriptFromFile(char* filename)
{
	FILE* inputFile = fopen(filename, "rb");
	fseek(inputFile, 0, SEEK_END);
	unsigned int filesize = ftell(inputFile);
	rewind(inputFile);
	char* script = calloc(filesize + 1, sizeof *script);
	if (script != NULL)
		fread(script, sizeof *script, filesize, inputFile);
	fclose(inputFile);
	return script;
}