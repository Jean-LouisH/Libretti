#include <Libretti.h>
#include <SDL.h>
#include <string>

#include "ConsoleMenu.hpp"

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
	Libretti* libretti = lb_createAndAddLibrettiToCallback(fileName.c_str());

	do
	{
		cycleStart = SDL_GetTicks();
		lb_incrementAllPlayTimes(frameTime / MS_PER_S);
		cycleEnd = SDL_GetTicks();
		deltaSeconds = (cycleEnd - cycleStart) / MS_PER_S;
		double frameDelay = (MS_PER_S / fps) - (deltaSeconds * MS_PER_S);
		if (frameDelay > 0)
			SDL_Delay(frameDelay);
		frameTime = SDL_GetTicks() - cycleStart;
	} while (isRunning);

	lb_freeLibretti(libretti);
	SDL_Quit();
	return 0;
}