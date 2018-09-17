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

lb_Binary_u8 loadASCIIStringFromFile(char* filename)
{
	FILE* inputFile = fopen(filename, "rb");
	lb_Binary_u8 string;
	string.data = NULL;
	string.size = 0;
	if (inputFile != NULL)
	{
		fseek(inputFile, 0, SEEK_END);
		string.size = ftell(inputFile);
		rewind(inputFile);
		string.data = malloc(sizeof *string.data * (string.size + 1));
		if (string.data != NULL)
		{
			fread(string.data, sizeof *string.data, string.size, inputFile);
			string.data[string.size] = NULL;
		}
		fclose(inputFile);
	}
	return string;
}

void saveBinaryU8ToFile(lb_Binary_u8* binary, char* filename)
{
	FILE* outputFile = fopen(filename, "wb");
	if (outputFile != NULL)
	{
		fwrite(binary->data, sizeof(uint8_t), binary->size, outputFile);
		fclose(outputFile);
	}
}

void saveBinaryS16ToFile(lb_Binary_s16* binary, char* filename)
{
	FILE* outputFile = fopen(filename, "wb");
	if (outputFile != NULL)
	{
		fwrite(binary->data, sizeof(int16_t), binary->size, outputFile);
		fclose(outputFile);
	}
}

void appendBinaryU8ToFile(lb_Binary_u8* binary, char* filename)
{
	FILE* outputFile = fopen(filename, "a");
	if (outputFile != NULL)
	{
		fwrite(binary->data, sizeof(uint8_t), binary->size, outputFile);
		fclose(outputFile);
	}
}

void appendBinaryS16ToFile(lb_Binary_s16* binary, char* filename)
{
	FILE* outputFile = fopen(filename, "a");
	if (outputFile != NULL)
	{
		fwrite(binary->data, sizeof(int16_t), binary->size, outputFile);
		fclose(outputFile);
	}
}