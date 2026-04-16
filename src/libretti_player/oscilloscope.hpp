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
#include <libretti.h>

namespace Oscilloscope
{
	void initialize(SDL_Window* window, SDL_GLContext context);
	/**Renders audio waves to an OpenGL targeted window.*/
	void render_waveforms(SDL_Window* window, lb_Libretti* libretti);
}