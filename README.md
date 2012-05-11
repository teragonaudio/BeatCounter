BeatCounter
===========
BeatCounter is a simple plugin designed to facilitate beatmatching software
and turntables. It displays the current tempo in beats per minute (BPM), while
the bottom window displays an accumulated average over the last few seconds.
BeatCounter is the perfect tool for DJ's that want to integrate computer
effects or elements with turntables.

![BeatCounter Screenshot](http://static.teragonaudio.com/ta_beatcounter.jpg)

Sending MIDI Sync
-----------------
BeatCounter cannot send MIDI clock sync to a plugin host. Since BeatCounter
is merely an effect plugin, it is not capable of controlling the tempo of a
sequencer such as Ableton Live. This is a restriction of the AudioUnit/VST
plugin frameworks.

