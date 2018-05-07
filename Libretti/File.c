#include "include/File.h"
#include <stdio.h>

char* loadScriptFile(char* filename)
{
	FILE* inputFile = fopen(filename, "rb");
	unsigned int filesize;
	char* script;
	size_t result = 0;

	fseek(inputFile, 0, SEEK_END);
	filesize = ftell(inputFile);
	rewind(inputFile);
	script = (char*) malloc(sizeof(char) * filesize);
	if (script != 0)
		result = fread(script, 1, filesize, inputFile);

	fclose(inputFile);
	return script;
}