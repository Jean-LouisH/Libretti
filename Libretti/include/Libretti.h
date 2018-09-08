/**
*                      This file is part of:
*                          Libretti
*
* Libretti
*
* Structures the compiler, and waveform generator
* procedures by default for simplicity.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Libretti/blob/master/LICENSE
*/

#ifndef Libretti_h
#define Libretti_h

#include <stdint.h>

#include "Audio.h"
#include "Notes.h"
#include "NoteWaves.h"
#include "Runtime.h"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		lb_Audio* audio;
		lb_NoteWaves* noteWaves;
		lb_Runtime* runtime;
	}Libretti;

	Libretti* lb_createLibretti(const char* filename);
	lb_Audio* lb_createAudio(const char* filename);
	lb_NoteWaves* lb_createNoteWaves();
	lb_Runtime* lb_createRuntime();
	void lb_addLibrettiToCallback(Libretti* libretti);
	Libretti* lb_createAndAddLibrettiToCallback(const char* filename);
	int lb_validateScriptFile(const char* filename);
	void lb_compileAudioFromScriptFile(lb_Audio* audio, const char* filename);
	void lb_updateNoteWavesFromAudio(lb_NoteWaves* noteWaves, lb_Audio* audio, lb_Runtime* runtime);
	void lb_updateNotesFromAudio(lb_Note* currentNotes, lb_Audio* audio, lb_Runtime* runtime);
	void lb_updateNoteWavesFromNotes(lb_NoteWaves* noteWaves, lb_Note* currentNotes, uint8_t trackCount);
	void lb_incrementPlayTime(Libretti* libretti, double timeSeconds);
	void lb_incrementAllPlayTimes(double timeSeconds);
	void lb_load(Libretti* libretti, char* filename);
	void lb_play(Libretti* libretti);
	void lb_pause(Libretti* libretti);
	void lb_reset(Libretti* libretti);
	void lb_stop(Libretti* libretti);
	void lb_playAll();
	void lb_pauseAll();
	void lb_resetAll();
	void lb_stopAll();
	void lb_exportAudioToWAV(lb_Audio* audio, const char* name);
	void lb_freeRuntime(lb_Runtime* runtime);
	void lb_freeNoteWaves(lb_NoteWaves* noteWaves);
	void lb_freeAudio(lb_Audio* audio);
	void lb_freeLibretti(Libretti* libretti);

#ifdef __cplusplus
}
#endif

#endif /*Libretti_h*/