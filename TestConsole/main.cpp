#include <Libretti.h>
#include <SDL.h>
#include <string>

#include "ConsoleMenu.hpp"

#define RECORD_TEST 0
#define RECORDING_FILEPATH "audio_recording_dump.bin"

#define MS_PER_S 1000.0

int main(int argc, char* argv[])
{
	std::string fileName;
	const double fps = 60;
	double cycleStart = 0.0;
	double cycleEnd = 0.0;
	double deltaSeconds = 0.0;
	double frameTime = 0.0;
	bool isRunning = true;

	menu(&fileName);
#if !RECORD_TEST
	Libretti* libretti = lb_createAndAddLibrettiToCallback(fileName.c_str());
#else
	lb_Binary_s16* binary = lb_captureAudio();

	SDL_Window* window = SDL_CreateWindow(
		"Libretti Test Console",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		0);

	lb_saveBinaryS16ToFile(binary, RECORDING_FILEPATH);
#endif

	do
	{
		cycleStart = SDL_GetTicks();
#if !RECORD_TEST
		lb_incrementAllPlayTimes(frameTime / MS_PER_S);
#endif
		cycleEnd = SDL_GetTicks();
		double frameDelay = (MS_PER_S / fps) - (cycleEnd - cycleStart);
		if (frameDelay > 0)
			SDL_Delay(frameDelay);
		frameTime = SDL_GetTicks() - cycleStart;

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
	SDL_Quit();
	return 0;
}