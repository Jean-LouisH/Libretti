/**
*                      This file is part of:
*                          Libretti
*
* Callback
*
* Handles the audio thread and communicates with the main thread through userdata.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#ifndef Callback_h
#define Callback_h

#include <SDL_stdinc.h>
#include "callback_list.hpp"
#include <libretti.h>
#include <binary.h>
#include <stdint.h>


void initialize_callback();
void add_libretti_to_callback(lb_Libretti* libretti);
void remove_libretti_from_callback(int libretti_id);
lb_Libretti* create_and_add_libretti_to_callback(const char* filename);
lb_Libretti* create_and_add_empty_libretti_to_callback();
void increment_all_play_times(float delta_time);

/*Plays a sound in the WaveformGenerator until the duration is reached.
	* key			- the tone of the note
	* dynamic		- the volume or amplitude of the note
	* panning		- the direction of the audio in the L/R speaker configuration
	* timbre		- the type of instrument used to render the sound
	* articulation	- the manner in which the key is released.
	* Each parameter must be selected from its corresponding enum*/
lb_Libretti* play_note_for(
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
lb_Libretti* play_note(
	uint16_t key,
	uint16_t dynamic,
	uint8_t panning,
	uint8_t timbre);

/*Plays a sound with the minimal amount of info needed for most common case
	* key			- the tone of the note
	* dynamic		- the volume or amplitude of the note
	* Each parameter must be selected from its corresponding enum*/
lb_Libretti* play_simple_note_for(
	uint16_t key,
	uint16_t dynamic,
	float duration);

/*Infinitely plays a sound with the minimal amount of info needed for most common case
	* key			- the tone of the note
	* dynamic		- the volume or amplitude of the note
	* Each parameter must be selected from its corresponding enum*/
lb_Libretti* play_simple_note(
	uint16_t key,
	uint16_t dynamic);

/*Plays all Librettis in the global callback list.*/
void play_all();

/*Pause all Librettis in the global callback list.*/
void pause_all();

/*Resets all Librettis in the global callback list.*/
void reset_all();

/*Stops all Librettis in the global callback list.*/
void stop_all();

lb_BinaryS16* get_audio_capture_stream_buffer();
void initialize_audio_playback(CallbackList callback_list[]);
void initialize_audio_capture(lb_BinaryS16* binary);
void run_callback_play(void* userdata, Uint8* stream, int byte_length);
void run_callback_capture(void* userdata, Uint8* stream, int byte_length);
void finalize_audio_playback(CallbackList callback_list[]);
void finalize_callback();

#endif /*Callback_h*/