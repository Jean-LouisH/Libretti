#pragma once

typedef struct Timing
{
	double simulation;
	int cycle_start;
	int cycle_end;
	int cycle_delta;
	int frame_delay;
	int frame;
	Timing() :
		simulation(0.0),
		cycle_start(0),
		cycle_end(0),
		cycle_delta(0),
		frame_delay(0),
		frame(0){}
}Timing;