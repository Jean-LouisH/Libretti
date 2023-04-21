/**
*                      This file is part of:
*                          Libretti
*
* Notes
*
* The smallest unit of immediate sounds and channel data.
*
* Copyright (c) 2017-2021 Jean-Louis Haywood. All rights reserved.
*/

#ifndef Notes_h
#define Notes_h

#include <stdint.h>
#include "Binary.h"
#include "Effects.h"

typedef struct
{
	float amplitude;
	float frequency_Hz;
	int8_t panning;
	uint8_t timbre;
	uint8_t articulation;
	uint16_t cue;
	lb_Binary_s16 sample;
	lb_Effects effects;
}lb_Note;

enum panning
{
	LB_REAR_LEFT = -128,
	LB_FRONT_LEFT = -64,
	LB_CENTRE = 0,
	LB_FRONT_RIGHT = 64,
	LB_REAR_RIGHT = 127
};

enum timbre
{
	LB_SQUARE_WAVE,
	LB_SINE_WAVE,
	LB_TRIANGLE_WAVE,
	LB_SAWTOOTH_WAVE,
	LB_PULSE_10,
	LB_PULSE_25,
	LB_NOISE,
	LB_METALLIC,
	LB_SAMPLE
};

/*from Pianississimo to Fortississimo.
* Out of signed 16 bit audio amplitude values.*/
enum dynamics
{
	LB_PPP = 64,
	LB_PP = 128,
	LB_P = 256,
	LB_MP = 512,
	LB_MF = 1024,
	LB_F = 2048,
	LB_FF = 4096,
	LB_FFF = 8192,
};

/*Enumerates macros as notes according to the piano key frequencies
in Hertz (Hz) which are rounded to the nearest whole number.*/

/*R represents a musical rest.*/
enum keyFrequencies
{
	LB_R = 0,
	LB_A0 = 28,
	LB_Bf0 = 29,
	LB_B0 = 31,
	LB_C1 = 33,
	LB_Cs1 = 35,
	LB_D1 = 37,
	LB_Ef1 = 39,
	LB_E1 = 41,
	LB_F1 = 44,
	LB_Fs1 = 46,
	LB_G1 = 49,
	LB_Gs1 = 52,
	LB_A1 = 56,
	LB_Bf1 = 58,
	LB_B1 = 62,
	LB_C2 = 65,
	LB_Cs2 = 69,
	LB_D2 = 73,
	LB_Ef2 = 78,
	LB_E2 = 82,
	LB_F2 = 87,
	LB_Fs2 = 92,
	LB_G2 = 98,
	LB_Gs2 = 104,
	LB_A2 = 110,
	LB_Bf2 = 117,
	LB_B2 = 123,
	LB_C3 = 131,
	LB_Cs3 = 139,
	LB_D3 = 147,
	LB_Ef3 = 156,
	LB_E3 = 165,
	LB_F3 = 175,
	LB_Fs3 = 185,
	LB_G3 = 196,
	LB_Gs3 = 208,
	LB_A3 = 220,
	LB_Bf3 = 233,
	LB_B3 = 247,
	LB_C4 = 262,
	LB_Cs4 = 277,
	LB_D4 = 294,
	LB_Ef4 = 311,
	LB_E4 = 330,
	LB_F4 = 349,
	LB_Fs4 = 370,
	LB_G4 = 392,
	LB_Gs4 = 415,
	LB_A4 = 440,
	LB_Bf4 = 466,
	LB_B4 = 494,
	LB_C5 = 523,
	LB_Cs5 = 554,
	LB_D5 = 587,
	LB_Ef5 = 622,
	LB_E5 = 659,
	LB_F5 = 698,
	LB_Fs5 = 740,
	LB_G5 = 784,
	LB_Gs5 = 831,
	LB_A5 = 880,
	LB_Bf5 = 932,
	LB_B5 = 988,
	LB_C6 = 1047,
	LB_Cs6 = 1109,
	LB_D6 = 1175,
	LB_Ef6 = 1245,
	LB_E6 = 1319,
	LB_F6 = 1397,
	LB_Fs6 = 1480,
	LB_G6 = 1568,
	LB_Gs6 = 1661,
	LB_A6 = 1760,
	LB_Bf6 = 1865,
	LB_B6 = 1976,
	LB_C7 = 2093,
	LB_Cs7 = 2217,
	LB_D7 = 2349,
	LB_Ef7 = 2489,
	LB_E7 = 2637,
	LB_F7 = 2794,
	LB_Fs7 = 2960,
	LB_G7 = 3136,
	LB_Gs7 = 3322,
	LB_A7 = 3520,
	LB_Bf7 = 3729,
	LB_B7 = 3951,
	LB_C8 = 4186
};

enum articulation
{
	LB_NORMAL,
	LB_SLUR,
	LB_STACCATO
};


#endif /*Notes_h*/