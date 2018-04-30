# Libretti

Libretti is a prototype synthesizer that plays through stereo channels with a number of simple waveform timbres. It uses an interpreter to read text files that are written with a custom scripting language:

Libretti language Specifications

Reference: https://en.wikipedia.org/wiki/List_of_musical_symbols

* "X" in the following specifications denote any of the note values.
* Entries in the format of  "symbol X" ... "Y symbol" denote a notation that spans multiple notes.
* "N" denotes numerical (whole and fractional) durations in this document only.
* "R" is a rest note.

* Notes: "A", "B", "C", "D", "E", "F", "G", "R"
* Accidentals: "#", "b", "n"
* Bar Line: "|"
* Duration: "/4", "/2", "1", "2" ,"3", "4", etc.
* Staccato: "XN*"
* Dotted: "XN."
* Slur/Tie: "~X" ... "Y~"
* Higher Octave: "+X"
* Lower Octave: "-X"
* Header tag: "[keyword: attribute]"
* Voice scope: "{main headers, notes & inline headers}"

* Headers: "Name", "KeySig", "TimeSig", "Tempo", "Channel", "Timbre", "Octave", "Dynamic", "RepeatBar", "End"
* Time Signatures: "1/4", "2/4", "3/4", "4/4", etc
* Key Signatures: "A Major", "A Minor", "B Major", "C Major", "C Minor", etc
* Tempo: "Largo" (50 bpm), "Adagio" (70 bpm), "Adante" (90 bpm), "Moderato" (110 bpm), "Allegro" (140 bpm), "Presto" (180 bpm), or type the bpm value directly.
* Channel: "Left", "Right", "Mono"
* Timbre: "Square Wave", "Sine Wave", "Triangle Wave", "Sawtooth Wave", "Pulse 10%", "Pulse 25%"
* Octave: "1", "2", "3", "4", "5", "6", "7", "8", etc
* Dynamic: "ppp", "pp", "p", "mp", "mf", "f", "ff", "fff"

* After and before every bar, there should be a space. This helps with the syncrhonization algorithm.

==============
Example:

"[Name: Mary had a little lamb]
[KeySig: G Major]
[TimeSig: 4/4]
[Tempo: Presto]
[Dynamic: mf]

{
[Channel: Mono]
[Timbre: Square Wave]
[Octave: 5] 

| ~ B1 A1 G1 A1 ~ | B1 B1 B2* | A1 A1 A2* | B1 +D1 D2 |
 ~ -B1 A1 G1 A1 ~ |  B1 B1 B1 B1 | A1 A1 B1 A1 | G2 R2 |
}

{
[Channel: Mono]
[Timbre: Triangle Wave]
[Octave: 4] 

| ~ G2 D2 | G2 D2 | C2 D2 | G2 D2 | G2 D2 |
 G2 D2 | C2 D2 | G2 R2 ~ | 
}
"






