#pragma once

typedef struct Timing
{
	double simulation;
	int cycleStart;
	int cycleEnd;
	int cycleDelta;
	int frameDelay;
	int frame;
	Timing() :
		simulation(0.0),
		cycleStart(0),
		cycleEnd(0),
		cycleDelta(0),
		frameDelay(0),
		frame(0){}
}Timing;