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

#include "Audio.h"
#include "CallbackData.h"
#include "Notes.h"
#include "NoteWaves.h"
#include "Runtime.h"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		lb_NoteWaves noteWaves;
		lb_Audio audio;
		lb_CallbackData callbackData;
		lb_Runtime runtime;
	}Libretti;

	int lb_libraryCompilationTest();
	void lb_initLibretti(Libretti* libretti);
	void lb_initCallbackData(lb_CallbackData* callbackData, lb_Audio* audio, lb_NoteWaves* noteWaves);
	void lb_initAudioRuntime(lb_Runtime* runtime, lb_CallbackData* callbackData);
	void lb_compileAudioFromScriptFile(lb_Audio* audio, char* filename);
	void lb_updateNotesFromAudio(lb_Note* notes, unsigned char* noteCount, lb_Audio* audio);
	void lb_updateNoteWavesFromAudio(lb_NoteWaves* noteWaves, lb_Audio* audio);
	void lb_updateNoteWavesFromNotes(lb_NoteWaves* noteWaves, lb_Note* notes, unsigned char* noteCount);
	void lb_incrementPlayTime(lb_Runtime* runtime, double timeSeconds);
	void lb_load(lb_Runtime* runtime, lb_Audio* audio, char* filename);
	void lb_play(lb_Runtime* runtime);
	void lb_pause(lb_Runtime* runtime);
	void lb_reset(lb_Runtime* runtime);
	void lb_stop(lb_Runtime* runtime);
	void lb_freeLibretti(Libretti* libretti);

#ifdef __cplusplus
}
#endif

#endif /*Libretti_h*/