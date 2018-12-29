#pragma once

#include <SDL.h>
#include <Libretti.h>
#include "Timing.hpp"
#include <string>

class ApplicationWindow
{
private:
	SDL_Window* window;
	SDL_GLContext context;
	Timing time;
	int windowWidth;
	int windowHeight;
public:
	ApplicationWindow(std::string appName);
	~ApplicationWindow();
	bool handleEvents(Libretti* libretti);
	void swapBuffers();
	int getFrameTime();
	SDL_Window* getSDLWindow();
};