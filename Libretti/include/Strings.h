/**
*                      This file is part of:
*                          Libretti
*
* Strings
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

typedef struct
{
	char* data;
	int length;
	int capacity;
}lb_String;

lb_String newString(int capacity);
void append(lb_String* string, char symbol);
void clear(lb_String* string);