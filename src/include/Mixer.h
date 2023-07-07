/**
*                      This file is part of:
*                          Libretti
*
* Mixer
*
* Applies effects to the note wave streams before sending to the audio device.
*
* Copyright (c) 2017-2021 Jean-Louis Haywood. All rights reserved.
*/

#ifndef Mixer_h
#define Mixer_h

#include "SDL_stdinc.h"
#include "Waveform.h"

/*Copies the note waves and assign audio values to the 5.1 surround channel array.*/
void interleaveWaveformToStream(Sint16 outputStream[], lb_Waveform* waveform);

#endif /*Mixer_h*/