/**
*                      This file is part of:
*                          Libretti
*
* File
*
* Handles input/output for scripting and file formats.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef File_h
#define File_h

#include <stdbool.h>
#include "Binary.h"

bool exists(char* filename);
lb_Binary_u8 loadASCIIStringFromFile(char* filename);
lb_Binary_u8 loadBinaryU8FromFile(char* filename);
lb_Binary_s16 loadBinaryS16FromFile(char* filename);
void saveBinaryU8ToFile(lb_Binary_u8* binary, char* filename);
void saveBinaryS16ToFile(lb_Binary_s16* binary, char* filename);
void appendBinaryU8ToFile(lb_Binary_u8* binary, char* filename);
void appendBinaryS16ToFile(lb_Binary_s16* binary, char* filename);

#endif /*File_h*/