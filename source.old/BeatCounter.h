/*
 *  BeatCounter - BeatCounter.h
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */


#ifndef __BeatCounter_h__
#define __BeatCounter_h__

#include "juce_amalgamated.h"
#include <vector>

#ifndef __BeatCounterModel_h__
#include "BeatCounterModel.h"
#endif

#ifndef __PluginParameterSet_h__
#include "PluginParameterSet.h"
#endif

namespace teragon {
  const double kMaxAutofilterFrequency = 400.0f;
  const double kMinAutofilterFrequency = 50.0f;
  // TODO: Change to use downsampling factor
  const long kDownsampleRate = 1000;
  const double kSilenceThreshold = 0.1;
  const double kDefaultTempo = 120.0;
  const double kMinimumTempo = 60.0;
  const double kMaximumTempo = 180.0;
  const double kHostTempoLinkToleranceInBpm = 16.0;
  
  const int kDecimalDisplayPrecision = 2;
  
  enum Parameters {
    kParamReset,
    kParamTolerance,
    kParamPeriod,
    kParamAutofilterEnabled,
    kParamAutofilterFrequency,
    kParamLinkToHostTempo,
    
    kNumParams
  };

  class BeatCounter : public AudioProcessor, public BeatCounterModel {
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

    // Programs (not supported)
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
    void getStateInformation(MemoryBlock& destData) {}
    void setStateInformation(const void* data, int sizeInBytes) {}
    
    // Model interface implementation
    const float getCurrentBpm() const;
    const float getRunningBpm() const;
    void setHostLink(bool isEnabled);
    void setAutofilter(bool isEnabled);

  private:
    double calculateAutofilterConstant(double sampleRate, double frequency) const;
    double getHostTempo() const;
    
    pluginParameters::PluginParameterSet* parameters;

    bool isAutofilterEnabled;
    double autofilterOutput;
    double autofilterConstant;
    double autofilterFrequency;
    
    double tolerance;
    double currentBpm;
    double runningBpm;
    long periodSizeInSamples;
    bool linkWithHostTempo;
    
    std::vector<double> bpmHistory;

    // OLD MEMBER VARIABLES
    
    bool m_beat_state;
    
    double *m_downsampled;
    double m_high_point;
    double m_bar_high_point;
    double m_bar_high_avg;
    double m_bar_samp_avg;
    double m_total_seconds_running;
    double m_last_avg;
    double m_min_bpm;
    double m_max_bpm;
    
    double m_autofilter_const;
    double m_autofilter_freq;
    double m_autofilter_out1;
    
    int m_downsampled_index;
    int m_beat_marks_index;
    int m_avg_bpm_index;
    
    unsigned long m_skip_count;
    unsigned long m_downsample_rate;
    unsigned long m_last_beat_counted;
    unsigned long m_num_samples_processed;
    unsigned long m_dupe_interval;
    unsigned long m_beat_samples;
  };
}

#endif
