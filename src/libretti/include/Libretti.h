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
		int id;
	}lb_Libretti;

	/*Allocates and returns a Libretti without adding to callback. */
	LIBRETTI_API void lb_initialize();

	/*Allocates and returns a Libretti without adding to callback. */
	LIBRETTI_API lb_Libretti* lb_createLibretti(const char* filename);

	/*Allocates and returns an empty Libretti without adding to callback. */
	LIBRETTI_API lb_Libretti* lb_createEmptyLibretti();

	/*Returns an audio struct with a compiled script.*/
	LIBRETTI_API lb_Audio* lb_createAudio(const char* filename);

	/*Returns an empty audio struct with a compiled script.*/
	LIBRETTI_API lb_Audio* lb_createEmptyAudio();

	/*Returns an clear, empty note wave stream struct.*/
	LIBRETTI_API lb_NoteWaves* lb_createNoteWaves();

	/*Returns runtime data with resetted time and device index for SDL audio.*/
	LIBRETTI_API lb_Runtime* lb_createRuntime();

	/*Updates the global callback list to playback Libretti simultaneously.*/
	LIBRETTI_API void lb_addLibrettiToCallback(lb_Libretti* libretti);

	/*Removes an active Libretti from the callback using its ID.*/
	LIBRETTI_API void lb_removeLibrettiFromCallback(int librettiID);

	/*Allocates and returns a Libretti with the global callback list updated.*/
	LIBRETTI_API lb_Libretti* lb_createAndAddLibrettiToCallback(const char* filename);

	/*Allocates and returns an empty Libretti with the global callback list updated.*/
	LIBRETTI_API lb_Libretti* lb_createAndAddEmptyLibrettiToCallback();

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
	LIBRETTI_API void lb_incrementPlayTime(lb_Libretti* libretti, float deltaTime_s);

	/*Updates the times of all Librettis in the global callback list.*/
	LIBRETTI_API void lb_incrementAllPlayTimes(float deltaTime_s);

	/*Updates an existing Libretti with a compiled script.*/
	LIBRETTI_API void lb_load(lb_Libretti* libretti, const char* filename);

	/*Allows the Libretti's runtime to increment time.*/
	LIBRETTI_API void lb_play(lb_Libretti* libretti);

	/*Plays a sound in the WaveformGenerator until the duration is reached.
	 * key			- the tone of the note
	 * dynamic		- the volume or amplitude of the note
	 * panning		- the direction of the audio in the L/R speaker configuration
	 * timbre		- the type of instrument used to render the sound
	 * articulation	- the manner in which the key is released.
	 * Each parameter must be selected from its corresponding enum*/
	LIBRETTI_API lb_Libretti* lb_play_note_for(
		uint16_t key,
		uint16_t dynamic,
		uint8_t panning,
		uint8_t timbre,
		uint8_t articulation,
		float duration);

	/*Infinitely plays a sound in the WaveformGenerator.
	 * key			- the tone of the note
	 * dynamic		- the volume or amplitude of the note
	 * panning		- the direction of the audio in the L/R speaker configuration
	 * timbre		- the type of instrument used to render the sound
	 * Each parameter must be selected from its corresponding enum*/
	LIBRETTI_API lb_Libretti* lb_play_note(
		uint16_t key,
		uint16_t dynamic,
		uint8_t panning,
		uint8_t timbre);

	/*Plays a sound with the minimal amount of info needed for most common case
	 * key			- the tone of the note
	 * dynamic		- the volume or amplitude of the note
	 * Each parameter must be selected from its corresponding enum*/
	LIBRETTI_API lb_Libretti* lb_play_simple_note_for(
		uint16_t key,
		uint16_t dynamic,
		float duration);

	/*Infinitely plays a sound with the minimal amount of info needed for most common case
	 * key			- the tone of the note
	 * dynamic		- the volume or amplitude of the note
	 * Each parameter must be selected from its corresponding enum*/
	LIBRETTI_API lb_Libretti* lb_play_simple_note(
		uint16_t key,
		uint16_t dynamic);

	/*Stops the Libretti's runtime from incrementing time.*/
	LIBRETTI_API void lb_pause(lb_Libretti* libretti);

	/*Sets the Libretti's runtime to 0.0s.*/
	LIBRETTI_API void lb_reset(lb_Libretti* libretti);

	/*Resets and Pauses the Libretti's runtime.*/
	LIBRETTI_API void lb_stop(lb_Libretti* libretti);

	/*Plays all Librettis in the global callback list.*/
	LIBRETTI_API void lb_playAll();

	/*Pause all Librettis in the global callback list.*/
	LIBRETTI_API void lb_pauseAll();

	/*Resets all Librettis in the global callback list.*/
	LIBRETTI_API void lb_resetAll();

	/*Stops all Librettis in the global callback list.*/
	LIBRETTI_API void lb_stopAll();

	/*Allocates and returns a region in memory that captures the incoming stream recording.*/
	LIBRETTI_API lb_BinaryS16* lb_getAudioCaptureStreamBuffer();

	/*Writes a file streamed in unsigned 8-bits.*/
	LIBRETTI_API void lb_saveBinaryU8ToFile(lb_BinaryU8* binary, const char* filename);

	/*Writes a file streamed in signed 16-bits.*/
	LIBRETTI_API void lb_saveBinaryS16ToFile(lb_BinaryS16* binary, const char* filename);

	/*Appends a file streamed in unsigned 8-bits.*/
	LIBRETTI_API void lb_appendBinaryU8ToFile(lb_BinaryU8* binary, const char* filename);

	/*Appends a file streamed in signed 16-bits.*/
	LIBRETTI_API void lb_appendBinaryS16ToFile(lb_BinaryS16* binary, const char* filename);

	/*Decodes an audio struct to a PCM stream.*/
	LIBRETTI_API lb_BinaryS16 lb_getSpectrumData(lb_Audio* audio);

	/*Deletes runtime memory allocation.*/
	LIBRETTI_API void lb_freeRuntime(lb_Runtime* runtime);

	/*Deletes note wave memory allocation.*/
	LIBRETTI_API void lb_freeNoteWaves(lb_NoteWaves* noteWaves);

	/*Deletes audio memory allocation.*/
	LIBRETTI_API void lb_freeAudio(lb_Audio* audio);

	/*Deletes memory allocation of runtime, note waves and audio, and the container Libretti.*/
	LIBRETTI_API void lb_freeLibretti(lb_Libretti* libretti);

	LIBRETTI_API void lb_finalize();

#ifdef __cplusplus
}
#endif

#endif /*Libretti_h*/