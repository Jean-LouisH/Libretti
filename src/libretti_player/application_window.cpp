#include "application_window.hpp"
#include "console_menu.hpp"
#include <SDL_audio.h>
#include <SDL_events.h>

#define FRAME_TIME_ms 17

ApplicationWindow::ApplicationWindow(std::string app_name)
{
	std::string displayed_app_name = app_name;
	this->window_width = 800;
	this->window_height = 600;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log(
			"SDL could not initialize because: %s",
			SDL_GetError());
	}

	this->window = SDL_CreateWindow(
		displayed_app_name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
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

bool ApplicationWindow::handle_events(lb_Libretti* libretti)
{
	SDL_Event SDLEvents;
	bool is_running = true;

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			is_running = false;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				is_running = false;
			}
			else if (SDLEvents.key.keysym.sym == SDLK_p)
			{
				if (libretti->playback->play_states & LB_PLAYBACK_STATE_IS_PLAYING)
				{
					lb_pause(libretti);
					SDL_PauseAudioDevice(libretti->playback->audio_device_id, true);
				}
				else
				{
					lb_play(libretti);
					SDL_PauseAudioDevice(libretti->playback->audio_device_id, false);
				}
			}
			else if (SDLEvents.key.keysym.sym == SDLK_s)
			{
				lb_stop(libretti);
				SDL_PauseAudioDevice(libretti->playback->audio_device_id, true);
			}
			else if (SDLEvents.key.keysym.sym == SDLK_r)
			{
				lb_reset(libretti);
				SDL_PauseAudioDevice(libretti->playback->audio_device_id, false);
			}
			else if (SDLEvents.key.keysym.sym == SDLK_l)
			{
				std::string filename;
				lb_stop(libretti);
				SDL_PauseAudioDevice(libretti->playback->audio_device_id, true);
				SDL_HideWindow(this->window);
				menu(&filename);
				lb_load(libretti, filename.c_str());
				lb_play(libretti);
				SDL_PauseAudioDevice(libretti->playback->audio_device_id, false);
				SDL_ShowWindow(this->window);
			}
			break;
		}
	}

	return is_running;
}

void ApplicationWindow::swap_buffers()
{
	time.cycle_end = SDL_GetTicks();
	time.cycle_delta = time.cycle_end - time.cycle_start;
	time.frame_delay = FRAME_TIME_ms - time.cycle_delta;
	if (time.frame_delay > 0)
		SDL_Delay(time.frame_delay);
	time.frame = SDL_GetTicks() - time.cycle_start;
	SDL_GL_SwapWindow(this->window);
	time.cycle_start = SDL_GetTicks();
}

int ApplicationWindow::get_frame_time()
{
	return this->time.frame;
}

SDL_Window* ApplicationWindow::get_sdl_window()
{
	return this->window;
}