/**
*                      This file is part of:
*                          Libretti
*
* Effects
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef Effects_h
#define Effects_h

typedef struct
{
	double preDelay_ms;
	double roomSize_pct;
	double damping_pct;
}ReverbControl;

typedef struct
{
	double delay_ms;
	double decay_pct;
}EchoControl;

typedef struct
{
	double level_dB;
}EQControl;

typedef struct
{
	double extent_cents;
	double rate_per_s;
}VibratoControl;

typedef struct
{
	ReverbControl reverb;
	EchoControl echo;
	EQControl eq[10]; //31Hz, 62Hz, 125Hz, 250Hz, 500Hz, 1kHz, 2kHz, 4kHz, 8kHz, 16kHz
	VibratoControl vibrato;
	uint32_t crossfading_ms;
	double pitchBlend_pct;
}lb_Effects;

#endif /*Effects_h*/