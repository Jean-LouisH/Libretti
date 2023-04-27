#include "ApplicationWindow.hpp"
#include "ConsoleMenu.hpp"
#include <SDL_events.h>

#define FRAME_TIME_ms 17

ApplicationWindow::ApplicationWindow(std::string appName)
{
	std::string displayedAppName = appName;
	this->windowWidth = 800;
	this->windowHeight = 600;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log(
			"SDL could not initialize because: %s",
			SDL_GetError());
	}

	this->window = SDL_CreateWindow(
		displayedAppName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_OPENGL);

	if (this->window == NULL)
	{
		SDL_Log(
			"SDL could not create the window because: %s",
			SDL_GetError());
	}

	this->context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(0);
}

ApplicationWindow::~ApplicationWindow()
{
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

bool ApplicationWindow::handleEvents(lb_Libretti* libretti)
{
	SDL_Event SDLEvents;
	bool isRunning = true;

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			isRunning = false;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
			else if (SDLEvents.key.keysym.sym == SDLK_p)
			{
				if (libretti->runtime->playStates & LB_RUNTIME_STATE_IS_PLAYING)
				{
					lb_pause(libretti);
				}
				else
				{
					lb_play(libretti);
				}
			}
			else if (SDLEvents.key.keysym.sym == SDLK_s)
			{
				lb_stop(libretti);
			}
			else if (SDLEvents.key.keysym.sym == SDLK_r)
			{
				lb_reset(libretti);
			}
			else if (SDLEvents.key.keysym.sym == SDLK_l)
			{
				std::string filename;
				lb_stop(libretti);
				SDL_HideWindow(this->window);
				menu(&filename);
				lb_load(libretti, filename.c_str());
				lb_play(libretti);
				SDL_ShowWindow(this->window);
			}
			break;
		}
	}

	return isRunning;
}

void ApplicationWindow::swapBuffers()
{
	time.cycleEnd = SDL_GetTicks();
	time.cycleDelta = time.cycleEnd - time.cycleStart;
	time.frameDelay = FRAME_TIME_ms - time.cycleDelta;
	if (time.frameDelay > 0)
		SDL_Delay(time.frameDelay);
	time.frame = SDL_GetTicks() - time.cycleStart;
	SDL_GL_SwapWindow(this->window);
	time.cycleStart = SDL_GetTicks();
}

int ApplicationWindow::getFrameTime()
{
	return this->time.frame;
}

SDL_Window* ApplicationWindow::getSDLWindow()
{
	return this->window;
}