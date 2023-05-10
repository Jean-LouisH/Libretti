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

#if !RECORD_TEST
	ApplicationWindow appWindow = ApplicationWindow("Libretti Playback Tests");
	SDL_HideWindow(appWindow.getSDLWindow());
#endif
	menu(&fileName);
	SDL_ShowWindow(appWindow.getSDLWindow());
#if !RECORD_TEST
	lb_initialize();
	lb_Libretti* libretti = lb_createAndAddLibrettiToCallback(fileName.c_str());
#else
	lb_Binary_s16* binary = lb_captureAudio();

	SDL_Window* window = SDL_CreateWindow(
		"Libretti Recording Test Console",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		0);

	lb_saveBinaryS16ToFile(binary, RECORDING_FILEPATH);
#endif

	Oscilloscope::initialize();

	do
	{
#if !RECORD_TEST
		isRunning = appWindow.handleEvents(libretti);
		Oscilloscope::renderWaveforms(appWindow.getSDLWindow(), libretti);
		lb_incrementAllPlayTimes(appWindow.getFrameTime() / MS_PER_S);
#endif
		appWindow.swapBuffers();

#if RECORD_TEST
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
#endif
	} while (isRunning);

#if !RECORD_TEST
	lb_freeLibretti(libretti);
#else
	SDL_DestroyWindow(window);
#endif
	lb_finalize();
	SDL_Quit();
}