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
	void initialize();
	/**Renders audio waves to an OpenGL targeted window.*/
	void renderWaveforms(SDL_Window* window, lb_Libretti* libretti);
}