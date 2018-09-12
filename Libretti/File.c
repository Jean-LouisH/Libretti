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

lb_Binary loadBinaryFromFile(char* filename)
{
	FILE* inputFile = fopen(filename, "rb");
	lb_Binary binary;
	binary.data = NULL;
	binary.size = 0;
	if (inputFile != NULL)
	{
		fseek(inputFile, 0, SEEK_END);
		binary.size = ftell(inputFile);
		rewind(inputFile);
		binary.data = malloc(sizeof *binary.data * (binary.size + 1));
		if (binary.data != NULL)
		{
			fread(binary.data, sizeof *binary.data, binary.size, inputFile);
			binary.data[binary.size] = NULL;
		}
		fclose(inputFile);
	}
	return binary;
}