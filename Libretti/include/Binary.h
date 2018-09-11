/**
*                      This file is part of:
*                          Libretti
*
* Binary
*
* Defines the basic data structure of incoming and outgoing file binaries.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#include <stdint.h>

#ifndef Binary_h
#define Binary_h

typedef struct
{
	uint8_t data;
	uint32_t fileSize;
}lb_Binary;

#endif /*Binary_h*/