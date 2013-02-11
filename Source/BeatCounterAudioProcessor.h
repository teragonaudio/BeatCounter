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

static const double kMaxAutofilterFrequency = 400.0f;
static const double kMinAutofilterFrequency = 50.0f;
// TODO: This is very suspicious and needs tweaking
static const long kDownsampleFactor = 1000;
static const double kSilenceThreshold = 0.1;
static const double kDefaultTempo = 120.0;
static const double kMinimumTempo = 60.0;
static const double kMaximumTempo = 180.0;
static const double kHostTempoLinkToleranceInBpm = 16.0;

enum Parameters {
    kParamReset,
    kParamTolerance,
    kParamPeriod,
    kParamAutofilterEnabled,
    kParamAutofilterFrequency,
    kParamLinkToHostTempo,

    kNumParams
};

static const float kParamToleranceMinValue = 0.0f;
static const float kParamToleranceMaxValue = 100.0f;
static const float kParamPeriodMinValue = 5.0f;
static const float kParamPeriodMaxValue = 20.0f;
static const float kParamAutofilterMinValue = 50.0f;
static const float kParamAutofilterMaxValue = 500.0f;

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
    void reset();
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
    String getParameterNameForStorage(int index) const;
    float getParameterScaled(float rawValue, float minValue, float maxValue) const;
    float getParameterFrequency(double rawValue, float minValue, float maxValue) const;
    void setParameterScaled(double *destination, float scaledValue, float minValue, float maxValue);
    void setParameterFrequency(double *destination, float scaledValue, float minValue, float maxValue);
    bool isParameterStored(int index) const;

    double calculateAutofilterConstant(double sampleRate, double frequency) const;
    double getHostTempo() const;

private:
    // Variables used by the autofilter
    bool autofilterEnabled;
    double autofilterOutput;
    double autofilterConstant;
    double autofilterFrequency;

    double tolerance;
    double currentBpm;
    double runningBpm;
    unsigned long periodSizeInSamples;
    bool linkWithHostTempo;

    std::vector<double> bpmHistory;

    // OLD MEMBER VARIABLES
    // TODO: Bah, need to remove or rename these suckers

    bool currentlyInsideBeat;

    double highestAmplitude;
    double highestAmplitudeForBar;
    double m_bar_high_avg;
    double m_bar_samp_avg;
    double m_last_avg;
    double minimumAllowedBpm;
    double maximumAllowedBpm;

    unsigned long m_skip_count;
    unsigned long numSamplesProcessed;
    unsigned long cooldownPeriodInSamples;
    unsigned long m_beat_samples;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeatCounterAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_1E83B8E4__
