#include "SystemTests.hpp"

#include <Libretti.h>
#include <SDL.h>
#include <string>
#include "utilities/ApplicationWindow.hpp"
#include "utilities/Oscilloscope.hpp"
#include "utilities/ConsoleMenu.hpp"

#define RECORD_TEST 0
#define RECORDING_FILEPATH "audio_recording_dump.bin"
#define MS_PER_S 1000.0

void LibrettiTests::SystemTests::run()
{
	std::string fileName;
	bool isRunning = true;

	lb_initialize();

#if !RECORD_TEST
	ApplicationWindow appWindow = ApplicationWindow("Libretti Playback Demo");
	lb_Libretti* libretti = lb_createEmptyLibretti();

	if (libretti != NULL &&
		libretti->composition != NULL)
	{
		/* Loads a console menu for loading demos and tests.
		The prompt repeats until a valid file is selected. */

		SDL_HideWindow(appWindow.getSDLWindow());
		while (libretti->composition->validationStatuses != LB_VALIDATION_ALL_OK)
		{
			menu(&fileName);
			lb_compileCompositionFromScriptFile(libretti->composition, fileName.c_str());
		}
		SDL_ShowWindow(appWindow.getSDLWindow());
		lb_addLibrettiToCallback(libretti);

		Oscilloscope::initialize();

		do
		{
			isRunning = appWindow.handleEvents(libretti);
			Oscilloscope::renderWaveforms(appWindow.getSDLWindow(), libretti);
			lb_incrementAllPlayTimes(appWindow.getFrameTime() / MS_PER_S);
			appWindow.swapBuffers();
		} while (isRunning);

		lb_freeLibretti(libretti);
	}
#else
	ApplicationWindow appWindow = ApplicationWindow("Libretti Recording Demo");
	lb_Binary_s16* binary = lb_captureAudio();
	lb_saveBinaryS16ToFile(binary, RECORDING_FILEPATH);

	do
	{
		SDL_Event SDLEvents;

		while (SDL_PollEvent(&SDLEvents))
		{
			switch (SDLEvents.type)
			{
			case SDL_KEYUP:
				lb_saveBinaryS16ToFile(binary, RECORDING_FILEPATH);
				break;
			}
		}
	} while (isRunning);

	SDL_DestroyWindow(window);
#endif
	lb_finalize();
	SDL_Quit();
}