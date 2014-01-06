BeatCounter
===========

BeatCounter is a simple plugin designed to facilitate beatmatching software
and turntables. It displays the current tempo in beats per minute (BPM), and
an accumulated average over the last few seconds.  BeatCounter is the perfect
tool for DJ's that want to integrate computer effects with turntables or a
live band.

![BeatCounter User Interface](http://static.teragonaudio.com/ta_beatcounter.jpg)


Parameters
----------

BeatCounter has the following controls available in its plugin editor window:

* Current BPM: Shows the actual tempo in beats per minue, updated every beat.
* Running BPM: Shows the average tempo over the last few seconds. The number
  of seconds used when calculating this value can be set with the "Period"
  knob.
* Beat: This light will pulse with the beat. If you don't see it flashing in
  time with music, then try tweaking the filter and tolerance knobs until it
  starts to pulse in time.
* Reset: Press this button to recalibrate the plugin for the input source. The
  BPM display will briefly be reset to 0.0 and all BPM history will be erased.
  Other parameters will retain their settings.
* Use Host Tempo: When activated, BeatCounter will assume that the input
  source is roughly equal to the sequencer's tempo. This is most appropriate
  for experienced DJ's looking to get a fine-tuned BPM display in order to
    match the sequencer's tempo to this value. When activated, the minimum and
    maximum BPM will be forced to +/- 16BPM of the host sequencer's current
    tempo.
* Filter: Enables a lowpass filter to improve beat detection. This setting
  makes sense when beat-matching with electronic music, and hence is limited
  to at most 500 Hz. Users attempting to calculate tempo with a live drummer
  may find the filter too restrictive and should try disabling it for best
  results.
* Tolerance: Determines how loud a beat is relative to the loudest calculated
  sample. For music with a prominent and loud kick (like most dance music),
  the default value of 75% should be sufficient. For highly compressed music
  with little dynamic range, a higher value should be used. When tuning this
  knob, pay attention to the beat light, which should pulse in time with the
  kick drum when correctly tuned.
* Period: Determines how many seconds should be considered when calculating
  Running BPM.


Limitations
-----------

As BeatCounter was designed for beat-matching electronic dance music with a
host sequencer, it performs particularly well under these settings but may not
yield accurate results with other types of music. BeatCounter's calculation
algorithm assumes a 4/4 tempo, and expects either 2 or 4 beats (kick drums) to
be present every bar.

So for standard techno and house tracks, BeatCounter should be quite accurate.
BeatCounter has an internal range of 60-180 BPM, and it will double the BPM
for slow but consistent tempos. That is, if a song is 120BPM but has a kick on
every second beat (ie, on the 2/4), this would technically be 60BPM. However,
BeatCounter will double this value and display 120BPM, which is correct in
most cases.

This means that BeatCounter will not do well with unconventional beat
patterns. A tap BPM feature would be necessary to provide tempo hints, this
[feature is being considered][1] for a future version of the software.


Sending MIDI Beat Clock to Synchronize a Host
---------------------------------------------

An oft-requested feature for BeatCounter is the ability to send [MIDI beat
clock][2] so that a host could sync directly to this tempo. Unfortunately this
is not possible with the plug-in version of BeatCounter. Although there is no
technical limitation that would prohibit a host from syncing to MIDI beat
clock, no sequencer actually does this. That is, all popular sequencers
(including Ableton Live, Logic Pro X, and Cubase) ignore MIDI beat clock
messages sent from a plugin and cannot synchronize to this.

It would however be possible to send beat clock messages from a standalone
application, this is a [feature that is being considered][3] but might be
limited to Mac OSX and Linux only, due to the nature of virtual MIDI devices
on Windows.


[1]: https://github.com/teragonaudio/BeatCounter/issues/16
[2]: https://en.wikipedia.org/wiki/MIDI_beat_clock
[3]: https://github.com/teragonaudio/BeatCounter/issues/6
