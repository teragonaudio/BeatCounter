/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_1E83B8E4__
#define __PLUGINPROCESSOR_H_1E83B8E4__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginParameters.h"

using namespace teragon;

// Effectively downsamples input from 44.1kHz -> 11kHz
static const long kDownsampleFactor = 4;
static const double kSilenceThreshold = 0.1;
static const double kMinimumTempo = 60.0;
static const double kMaximumTempo = 180.0;
static const double kDefaultTempo = 120.0;
static const double kHostTempoLinkToleranceInBpm = 16.0;

static const int kParamToleranceMinValue = 1;
static const int kParamToleranceMaxValue = 100;
static const int kParamToleranceDefaultValue = 75;
static const float kParamPeriodMinValue = 1.0f;
static const float kParamPeriodMaxValue = 10.0f;
static const float kParamPeriodDefaultValue = 2.0f;
static const float kParamFilterMinValue = 50.0f;
static const float kParamFilterMaxValue = 500.0f;
static const float kParamFilterDefaultValue = 450.0f;

class BeatCounterAudioProcessor : public AudioProcessor, PluginParameterObserver {
public:
    BeatCounterAudioProcessor();
    ~BeatCounterAudioProcessor() {}

    // Playback
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources() {}
    void reset();
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    // Editor
    AudioProcessorEditor* createEditor();
    bool hasEditor() const { return true; }

    // Parameter handling
    int getNumParameters();
    float getParameter(int index);
    void setParameter(int index, float newValue);
    const String getParameterName(int index);
    const String getParameterText(int index);

    // Plugin configuration and basic properties
    const String getName() const { return JucePlugin_Name; }
    const String getInputChannelName(int channelIndex) const { return String(channelIndex + 1); }
    const String getOutputChannelName(int channelIndex) const { return String(channelIndex + 1); }
    bool isInputChannelStereoPair(int index) const { return true; }
    bool isOutputChannelStereoPair(int index) const { return true; }
    bool acceptsMidi() const { return true; }
    bool producesMidi() const { return true; }
    bool silenceInProducesSilenceOut() const { return true; }
    double getTailLengthSeconds() const { return 0.0; }

    // Program support (not needed by this plugin)
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram(int index) {}
    const String getProgramName(int index) { return String::empty; }
    void changeProgramName(int index, const String& newName) {}

    // State restore
    void getStateInformation(MemoryBlock& destData);
    void setStateInformation(const void* data, int sizeInBytes);

    // PluginParameterObserver methods
    virtual bool isRealtimePriority() const { return true; }
    virtual void onParameterUpdated(const PluginParameter *parameter);

private:
    double calculateFilterConstant(double sampleRate, double frequency) const;
    double getHostTempo() const;

private:
    ThreadsafePluginParameterSet parameters;

    // Cached parameters
    IntegerParameter *tolerance;
    FloatParameter *period;
    BooleanParameter *filterEnabled;
    FrequencyParameter *filterFrequency;
    BooleanParameter *useHostTempo;

    // Variables used by the lopass filter
    double filterOutput;
    double filterConstant;

    // Used to calculate the running BPM
    std::vector<double> bpmHistory;
    // Running BPM shown in GUI
    double runningBpm;
    // State of the processing algorithm, will be true if the current sample is part of the beat
    bool currentlyInsideBeat;
    // Highest known amplitude found since initialization (or reset)
    double highestAmplitude;
    // Highest known amplitude found within a period
    double highestAmplitudeInPeriod;
    // Running average of the number of samples found between beats. Used to calculate the actual BPM.
    double beatLengthRunningAverage;
    // Used to calculate the BPM in combination with beatLengthRunningAverage
    unsigned long numSamplesSinceLastBeat;
    // Smallest possible BPM allowed, can improve accuracy if input source known to be within a given BPM range
    double minimumAllowedBpm;
    // Largest possible BPM allowed, can improve accuracy if input source known to be within a given BPM range
    double maximumAllowedBpm;
    // Poor man's downsampling
    unsigned long samplesToSkip;
    // Used to calculate the period, which in turn effects the total accuracy of the algorithm
    unsigned long numSamplesProcessed;
    // Wait at least this many samples before another beat can be detected. Used to reduce the possibility
    // of crazy fast tempos triggered by static wooshing and other such things which may fool the trigger
    // detection algorithm.
    unsigned long cooldownPeriodInSamples;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeatCounterAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_1E83B8E4__
