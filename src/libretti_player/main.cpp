#include <libretti.h>
#include <string>
#include "application_window.hpp"
#include "oscilloscope.hpp"
#include "console_menu.hpp"
#include "callback.hpp"
#include <SDL.h>

#undef main //undo SDLmain definition

#define RECORD_TEST 0
#define RECORDING_FILEPATH "audio_recording_dump.bin"
#define MS_PER_S 1000.0

int main(int argc, char* argv[])
{
	std::string file_name;
	bool is_running = true;

	initialize_callback();

#if !RECORD_TEST
	ApplicationWindow app_window = ApplicationWindow("Libretti Playback Demo");
	lb_Libretti* libretti = lb_create_empty_libretti();

	if (libretti != NULL &&
		libretti->composition != 0)
	{
		/* Loads a console menu for loading demos and tests.
		The prompt repeats until a valid file is selected. */

		SDL_HideWindow(app_window.get_sdl_window());
		while (libretti->composition->validation_statuses != LB_VALIDATION_ALL_OK)
		{
			menu(&file_name);
			lb_compile_composition_from_script_file(libretti->composition, file_name.c_str());
		}
		SDL_ShowWindow(app_window.get_sdl_window());
		add_libretti_to_callback(libretti);

		Oscilloscope::initialize(app_window.get_sdl_window(), app_window.context);

		do
		{
			is_running = app_window.handle_events(libretti);
			Oscilloscope::render_waveforms(app_window.get_sdl_window(), libretti);
			increment_all_play_times(app_window.get_frame_time() / MS_PER_S);
			app_window.swap_buffers();
		} while (is_running);

		lb_free_libretti(libretti);
	}
#else
	ApplicationWindow app_window = ApplicationWindow("Libretti Recording Demo");
	lb_Binary_s16* binary = lb_capture_audio();
	lb_save_binary_s16_to_file(binary, RECORDING_FILEPATH);

	do
	{
		SDL_Event SDLEvents;

		while (SDL_PollEvent(&SDLEvents))
		{
			switch (SDLEvents.type)
			{
			case SDL_KEYUP:
				lb_save_binary_s16_to_file(binary, RECORDING_FILEPATH);
				break;
			}
		}
	} while (is_running);

	SDL_DestroyWindow(window);
#endif
	finalize_callback();
	SDL_Quit();

	return 0;
}
