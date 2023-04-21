/**
*                      This file is part of:
*                          Libretti
*
* Libretti
*
* Structures the compiler, and waveform generator
* procedures by default for simplicity.
*
* Copyright (c) 2017-2021 Jean-Louis Haywood. All rights reserved.
*/

#ifndef Libretti_h
#define Libretti_h

#include <stdint.h>

#include "Audio.h"
#include "Binary.h"
#include "Notes.h"
#include "NoteWaves.h"
#include "Runtime.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if defined (_WIN32)
#if defined(_LIBRETTI_EXPORTS)
#define  LIBRETTI_API __declspec(dllexport)
#else
#define  LIBRETTI_API __declspec(dllimport)
#endif
#else
#define LIBRETTI_API
#endif

	/*Read only audio, output note wave streams, playback runtime.*/
	typedef struct
	{
		lb_Audio* audio;
		lb_NoteWaves* noteWaves;
		lb_Runtime* runtime;
	}Libretti;

	/*Allocates and returns a Libretti without adding to callback. */
	LIBRETTI_API void lb_initialize();

	/*Allocates and returns a Libretti without adding to callback. */
	LIBRETTI_API Libretti* lb_createLibretti(const char* filename);

	/*Allocates and returns an empty Libretti without adding to callback. */
	LIBRETTI_API Libretti* lb_createEmptyLibretti();

	/*Returns an audio struct with a compiled script.*/
	LIBRETTI_API lb_Audio* lb_createAudio(const char* filename);

	/*Returns an empty audio struct with a compiled script.*/
	LIBRETTI_API lb_Audio* lb_createEmptyAudio();

	/*Returns an clear, empty note wave stream struct.*/
	LIBRETTI_API lb_NoteWaves* lb_createNoteWaves();

	/*Returns runtime data with resetted time and device index for SDL audio.*/
	LIBRETTI_API lb_Runtime* lb_createRuntime();

	/*Updates the global callback list to playback Libretti simultaneously.*/
	LIBRETTI_API void lb_addLibrettiToCallback(Libretti* libretti);

	/*Allocates and returns a Libretti with the global callback list updated.*/
	LIBRETTI_API Libretti* lb_createAndAddLibrettiToCallback(const char* filename);

	/*Allocates and returns an empty Libretti with the global callback list updated.*/
	LIBRETTI_API Libretti* lb_createAndAddEmptyLibrettiToCallback();

	/*Loads script and validates it against the language specification, returns validation codes.*/
	LIBRETTI_API int lb_validateScriptFile(const char* filename);

	/*Updates existing audio with compiled script.*/
	LIBRETTI_API void lb_compileAudioFromScriptFile(lb_Audio* audio, const char* filename);

	/*Updates existing note waves from audio at a given runtime.*/
	LIBRETTI_API void lb_updateNoteWavesFromAudio(lb_NoteWaves* noteWaves, lb_Audio* audio, lb_Runtime* runtime);

	/*Extract as many simultaneous notes that matches the audio track count, at a given runtime.*/
	LIBRETTI_API void lb_updateNotesFromAudio(lb_Note currentNotes[], lb_Audio* audio, lb_Runtime* runtime);

	/*Updates note waves with a PCM representation of the encoded notes.*/
	LIBRETTI_API void lb_updateNoteWavesFromNotes(lb_NoteWaves* noteWaves, lb_Note currentNotes[], uint8_t trackCount);

	/*Updates the Libretti's runtime with a delta in seconds.*/
	LIBRETTI_API void lb_incrementPlayTime(Libretti* libretti, float deltaTime_s);

	/*Updates the times of all Librettis in the global callback list.*/
	LIBRETTI_API void lb_incrementAllPlayTimes(float deltaTime_s);

	/*Updates an existing Libretti with a compiled script.*/
	LIBRETTI_API void lb_load(Libretti* libretti, const char* filename);

	/*Allows the Libretti's runtime to increment time.*/
	LIBRETTI_API void lb_play(Libretti* libretti);

	LIBRETTI_API Libretti* lb_play_key(uint16_t keyFrequency, float duration);

	/*Stops the Libretti's runtime from incrementing time.*/
	LIBRETTI_API void lb_pause(Libretti* libretti);

	/*Sets the Libretti's runtime to 0.0s.*/
	LIBRETTI_API void lb_reset(Libretti* libretti);

	/*Resets and Pauses the Libretti's runtime.*/
	LIBRETTI_API void lb_stop(Libretti* libretti);

	/*Plays all Librettis in the global callback list.*/
	LIBRETTI_API void lb_playAll();

	/*Pause all Librettis in the global callback list.*/
	LIBRETTI_API void lb_pauseAll();

	/*Resets all Librettis in the global callback list.*/
	LIBRETTI_API void lb_resetAll();

	/*Stops all Librettis in the global callback list.*/
	LIBRETTI_API void lb_stopAll();

	/*Allocates and returns a region in memory that captures the incoming stream recording.*/
	LIBRETTI_API lb_Binary_s16* lb_getAudioCaptureStreamBuffer();

	/*Writes a file streamed in unsigned 8-bits.*/
	LIBRETTI_API void lb_saveBinaryU8ToFile(lb_Binary_u8* binary, const char* filename);

	/*Writes a file streamed in signed 16-bits.*/
	LIBRETTI_API void lb_saveBinaryS16ToFile(lb_Binary_s16* binary, const char* filename);

	/*Appends a file streamed in unsigned 8-bits.*/
	LIBRETTI_API void lb_appendBinaryU8ToFile(lb_Binary_u8* binary, const char* filename);

	/*Appends a file streamed in signed 16-bits.*/
	LIBRETTI_API void lb_appendBinaryS16ToFile(lb_Binary_s16* binary, const char* filename);

	/*Decodes an audio struct to a PCM stream and encodes it in WAV file format.*/
	LIBRETTI_API void lb_exportAudioToWAV(lb_Audio* audio, const char* name);

	/*Deletes runtime memory allocation.*/
	LIBRETTI_API void lb_freeRuntime(lb_Runtime* runtime);

	/*Deletes note wave memory allocation.*/
	LIBRETTI_API void lb_freeNoteWaves(lb_NoteWaves* noteWaves);

	/*Deletes audio memory allocation.*/
	LIBRETTI_API void lb_freeAudio(lb_Audio* audio);

	/*Deletes memory allocation of runtime, note waves and audio, and the container Libretti.*/
	LIBRETTI_API void lb_freeLibretti(Libretti* libretti);

	LIBRETTI_API void lb_finalize();

#ifdef __cplusplus
}
#endif

#endif /*Libretti_h*/