## Libretti Version 1.0 Roadmap

* Can validate the contents of text files against the Libretti scripting specification.
* Can compile audio builds from scripts according to the Libretti scripting specification.
* Supports audio specifications
	- 44.1 kHz sample rate
	- 16 bit format
	- 5.1 channel
* Has mixer effects via notes;
	- Crossfading
	- Echo
	- EQ
	- Filtering
	- Pitch Blend
	- Reverb
	- Vibrato
* Has user application effects override;
	- All of the above mixing effects
	- Variable panning
	- Volume control
* Supports input device streams by comprising tracks of note, tempo and lyrics event units with statically allocated data.
* Has at least 21 general purpose tracks designed to simultaneously support at least:
	- 10 for keyboards
	- 5 for strings
	- 1 for voice/melody
	- 1 for bass
	- 2 for winds
	- 1 for electronic/primitives
	- 1 for percussion
* Supports the following timbres;
	- Sine 
	- Square
	- Triangle
	- Sawtooth
	- Pulse10
	- Pulse25
	- Noise
	- Metallic
	- Sampled (Referenced in script, defined in external file)
		- Piano
		- Guitar
		- Bass
		- Percussion
		- Strings
		- Brass
* Has application integration controls such as;
	- Repeating
	- Timbre swapping
	- Playing, Pausing, Stopping and Resetting
	- Audio fading transition
	- Cue control signals
	- Multiple audio builds in one callback
	- Play speed control