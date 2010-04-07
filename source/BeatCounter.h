/*
 *  BeatCounter - BeatCounter.h
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */


#ifndef __BeatCounter_h__
#define __BeatCounter_h__

/*
#ifndef __BeatCounterEditor_H
#include "BeatCounterEditor.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif
*/

#include "juce_amalgamated.h"

#include <vector>

namespace teragon {
  const double kMaxAutofilterFrequency = 400.0f;
  const double kMinAutofilterFrequency = 50.0f;

  class BeatCounter : public AudioProcessor {
  public:
    BeatCounter();
    ~BeatCounter();

    // Plugin name
    const String getName() const { return JucePlugin_Name; }
    
    // Parameters
    int getNumParameters() { return kNumParams; };
    const String getParameterName(int parameterIndex);
    float getParameter(int parameterIndex);
    const String getParameterText(int parameterIndex);
    void setParameter(int parameterIndex, float newValue);
    bool isParameterAutomatable(int parameterIndex) const { return false; }

    // Programs (currently not supported)
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram(int index) {}
    const String getProgramName(int index) { return String::empty; }
    void changeProgramName(int index, const String& newName) {}

    // I/O configuration
    const String getInputChannelName(const int channelIndex) const { return String(channelIndex + 1); }
    const String getOutputChannelName(const int channelIndex) const { return String(channelIndex + 1); }
    bool isInputChannelStereoPair(int index) const { return false; }
    bool isOutputChannelStereoPair(int index) const { return false; }

    // MIDI configuration
    bool acceptsMidi() const { return false; }
    bool producesMidi() const { return true; }

    // Audio processing
    void prepareToPlay(double sampleRate, int estimatedSamplesPerBlock);
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void releaseResources();
    void reset();

    // GUI editor
    AudioProcessorEditor* createEditor();

    // Save/restore
    void getStateInformation(JUCE_NAMESPACE::MemoryBlock& destData) {}
    void setStateInformation(const void* data, int sizeInBytes) {}

  private:
    double calculateAutofilterConstant(double sampleRate, double frequency) const;

    bool autofilterEnabled;
    double autofilterOutput;
    double autofilterConstant;
    double autofilterFrequency;
  /*
  public:
    BeatCounterCore(int num_params, int version, char *name);
    ~BeatCounterCore();
    
    const float fabs(float f) const;
    void process(float **inputs, float **outputs, long frames);
    void setEditor(BeatCounterEditor *e);
    void reset();
    
  protected:
  private:    
    void init();
    
    BeatCounterEditor *editor;
    std::vector<float> m_bpm_history;
    
    bool m_beat_state;
    
    float *m_downsampled;
    float m_high_point;
    float m_bar_high_point;
    float m_bar_high_avg;
    float m_bar_samp_avg;
    float m_total_seconds_running;
    float m_last_avg;
    float m_min_bpm;
    float m_max_bpm;
    
    float m_autofilter_const;
    float m_autofilter_freq;
    float m_autofilter_out1;
    
    int m_downsampled_index;
    int m_beat_marks_index;
    int m_avg_bpm_index;
    
    unsigned long m_skip_count;
    unsigned long m_downsample_rate;
    unsigned long m_last_beat_counted;
    unsigned long m_num_samples_processed;
    unsigned long m_dupe_interval;
    unsigned long m_beat_samples;
    */
  };
}

#endif
