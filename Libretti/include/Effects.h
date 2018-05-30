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
	double preDelay;
	double roomSize;
	double dampingPercentage;
}ReverbControl;

typedef struct
{
	double msDelay;
	double decayPercentage;
}EchoControl;

typedef struct
{
	double frequency;
	double levelPercentage;
}EQControl;

typedef struct
{
	double extent;
	double ratePerSecond;
}VibratoControl;

typedef struct
{
	ReverbControl reverb;
	EchoControl echo;
	EQControl* eq; //list of frequencies and levels.
	VibratoControl vibrato;
	double msCrossfading;
	double pitchBlendPercentage;
}lb_Effects;

#endif /*Effects_h*/