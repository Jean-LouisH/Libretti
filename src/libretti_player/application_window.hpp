#pragma once

#include <SDL.h>
#include <libretti.h>
#include "timing.hpp"
#include <string>

class ApplicationWindow
{
private:
	SDL_Window* window;
	Timing time;
	int window_width;
	int window_height;
public:
	SDL_GLContext context;
	
	ApplicationWindow(std::string app_name);
	~ApplicationWindow();
	bool handle_events(lb_Libretti* libretti);
	void swap_buffers();
	int get_frame_time();
	SDL_Window* get_sdl_window();
};