## Libretti Target Featureset


* The core is a specification and portable code file format

* Extensive track support with effects metadata.
- Mixer Interleave
- EQ
- Filtering
- Vibrato
- Pitch Blend
- Dynamics control
- Variable panning
- Reverb
- Echo
- Dynamic Range Compression
- Crossfading
- Flanging

* Streaming protocol and instrument digital interface support

* at least 21 general purpose tracks designed to simultaneously support at least:
-10 for keyboards
-5 for strings
-1 for voice/melody
-1 for bass
-2 for winds
-1 for electronic/primitives
-1 for percussion

* Timbres
-Sine 
-Square
-Triangle
-Sawtooth
-Pulse10
-Pulse25
-Noise
-Metallic
-Sampled (Referenced in script, defined in external file)
	Piano
	Guitar
	Bass
	Percussion
	Strings
	Brass
	Etc

* Synthesizer settings
-44.1kHz sample rate
-16-bit format
-5.1 channel

* Has an standalone application with visualizations and album in the background.
* Player oscilloscope
- Individual voice streams
- Combined voice streams

* Can be used as a library to integrate into games or other applications.
- Has repeat
- Has timbre swapping
- Can be played, paused, stopped, reset
- Audio fading transition
- Volume control
- Cue control signals
- Multiple audios to add audio scripted soundfx
- Adjust directionality
- Adjust play speed.

* Supports a custom scripting language
* Has error handling for scripting
* Common case all keywords
* Allows reading and writing of the bytecode file.
* Has a console interface that links to other internally supported applications.
* Has another standalone application for recording to bytecode conversion via note recognition.
* Has a image recognition sight reading standalone application
* Has another standalone application for editting bytecode
* Subtitle support according to notes being played