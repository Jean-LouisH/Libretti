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
	double frequency;
	double level_pct;
}EQControl;

typedef struct
{
	double extent;
	double rate_per_s;
}VibratoControl;

typedef struct
{
	ReverbControl reverb;
	EchoControl echo;
	EQControl* eq;
	uint16_t eqListSize;
	VibratoControl vibrato;
	double crossfading_ms;
	double pitchBlend_pct;
}lb_Effects;

#endif /*Effects_h*/