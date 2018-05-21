#include "include/File.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char exists(char* filename)
{
	FILE* inputFile = fopen(filename, "rb");
	fclose(inputFile);
	return (unsigned char)inputFile;
}

char* loadScriptFromFile(char* filename)
{
	FILE* inputFile = fopen(filename, "rb");
	fseek(inputFile, 0, SEEK_END);
	unsigned int filesize = ftell(inputFile);
	rewind(inputFile);
	char* script = malloc(sizeof *script * (filesize + 1));
	if (script != NULL)
	{
		fread(script, sizeof *script, filesize, inputFile);
		script[filesize] = NULL;
	}
	fclose(inputFile);
	return script;
}