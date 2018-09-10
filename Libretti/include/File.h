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

bool exists(char* filename);
char* loadBinaryFromFile(char* filename);

#endif /*File_h*/