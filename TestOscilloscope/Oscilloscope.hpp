/**
*                      This file is part of:
*                          Libretti
*
* Oscilloscope
*
* Renders raw streams.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once


#include <SDL.h>
#include <Libretti.h>

namespace Oscilloscope
{
	/** Creates a window and context targeted
	* at an oscilloscope that renders audio waves.*/
	void renderWaveforms(SDL_Window* window, Libretti* libretti);
}