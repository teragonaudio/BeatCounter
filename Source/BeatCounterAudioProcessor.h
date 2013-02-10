/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_1E83B8E4__
#define __PLUGINPROCESSOR_H_1E83B8E4__

#include "../JuceLibraryCode/JuceHeader.h"
#include "EditorViewController.h"

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


//==============================================================================
class BeatCounterAudioProcessor  : public AudioProcessor, public EditorViewController
{
public:
    //==============================================================================
    BeatCounterAudioProcessor();
    ~BeatCounterAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const { return true; }

    //==============================================================================
    const String getName() const { return JucePlugin_Name; }

    int getNumParameters() { return kNumParams; }

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const { return String(channelIndex + 1); }
    const String getOutputChannelName (int channelIndex) const { return String(channelIndex + 1); }
    bool isInputChannelStereoPair (int index) const { return true; }
    bool isOutputChannelStereoPair (int index) const { return true; }

    bool acceptsMidi() const { return true; }
    bool producesMidi() const { return true; }
    bool silenceInProducesSilenceOut() const { return true; }

    //==============================================================================
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram (int index) {}
    const String getProgramName (int index) { return String::empty; }
    void changeProgramName (int index, const String& newName) {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    const double getCurrentBpm() const;
    const double getRunningBpm() const;

    void onFilterButtonPressed(bool isEnabled);
    void onLinkButtonPressed(bool isEnabled);
    void onResetButtonPressed(bool isEnabled);

private:
    double calculateAutofilterConstant(double sampleRate, double frequency) const;
    double getHostTempo() const;


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
    // TODO: Bah, need to remove and rename these suckers

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

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeatCounterAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_1E83B8E4__
