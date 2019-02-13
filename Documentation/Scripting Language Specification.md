## Libretti scripting language Specifications

Reference: https://en.wikipedia.org/wiki/List_of_musical_symbols

* "X" in the following specifications denote any of the note values.
* Entries in the format of  "symbol X" ... "Y symbol" denote a notation that spans multiple notes.
* "N" denotes numerical (whole and fractional) durations in this document only.
* "R" is a rest note.

Notes: "A", "B", "C", "D", "E", "F", "G", "R"
Accidentals: "#", "b", "n"
Bar Line: "|"
Duration: "/4", "/2", "1", "2" ,"3", "4", etc.
Staccato: "XN*"
Dotted: "XN."
Slur/Tie: "~X" ... "Y~"
Higher Octave: "+X"
Lower Octave: "-X"
Tuplets: _XN YN ZN_
Crescendo: << XN YN... ZN <<
Diminuendo: >> XN YN... ZN >>
Accent: XN>
Header tag: "[keyword: attribute]"
Voice scope: "{main headers, notes & inline headers}"

-----------------------------------------------------
Headers;

name:
artist:
lyric:

time sig: "1/4", "2/4", "3/4", "4/4", etc
key sig: "a major", "a minor", "b major", "c major", "c minor", etc
tempo: "largo" (50 bpm), "adagio" (70 bpm), "adante" (90 bpm), "moderato" (110 bpm), "allegro" (140 bpm), "presto" (180 bpm), or type the bpm value directly.
timbre: "square wave", "sine wave", "triangle wave", "sawtooth wave", "pulse 10%", "pulse 25%"
octave: "1", "2", "3", "4", "5", "6", "7", "8", etc
dynamic: "ppp", "pp", "p", "mp", "mf", "f", "ff", "fff"

loop: "none", "[value]", "infinity"
segment:
end:

cue: [cue list is made at top of script with macro = value pairing]
panning: "far left", "left", "mono", "right", "far right", [floating point value -1.0 to +1.0]
reverb: "none", "standard", [room_size=percentage, pre-delay=ms, damping=percentage]
echo: "none", "standard", [delay=integer_value, decay=floating_point_value]
eq: "none" [[frequency_value]: [level]]
vibrato: "none", "standard"
flanging: "none", "standard"
crossfading: "none", [ms]
pitch blend: "none", [percentage]
----------------------------------------------------



==============
Example:

"[name: Mary had a little lamb][artist: Sarah Josepha Hale][key sig: G major][time sig: 4/4][tempo: presto]
[dynamic: mf][reverb: standard][vibrato: standard]

{
[panning: mono][timbre: square wave][octave: 5] 

[loop: infinity] ~ B1 A1 G1 A1 ~ | B1> B1> B2* [cue: 2] | A1> A1> A2* [cue: 12]| B1> +D1> _ D1 E1 D1 _ |
~ -B1 A1 G1 A1 ~ |  << B1 B1 B1 B1 << | >> A1 A1 B1 A1 | [echo: standard] G2 >> R2 |
}

{
[panning: mono][timbre: triangle wave][octave: 4] 

~ G2 D2 | G2 D2 | C2 D2 | G2 D2 | G2 D2 | G2 D2 | C2 D2 | G2 R2 ~ | 
}

{
[lyric: mary had a ] | [lyric: little lamb] | | | [lyric: mary had a ] | [lyric: little lamb, its] |  
[lyric: fleece were white as] | [lyric: snow] |
}
"