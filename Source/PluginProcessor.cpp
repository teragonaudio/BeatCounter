/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BeatCounterAudioProcessor::BeatCounterAudioProcessor()
{
}

BeatCounterAudioProcessor::~BeatCounterAudioProcessor()
{
}

//==============================================================================
const String BeatCounterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int BeatCounterAudioProcessor::getNumParameters()
{
    return 0;
}

float BeatCounterAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void BeatCounterAudioProcessor::setParameter (int index, float newValue)
{
}

const String BeatCounterAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String BeatCounterAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String BeatCounterAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String BeatCounterAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool BeatCounterAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool BeatCounterAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool BeatCounterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BeatCounterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BeatCounterAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

int BeatCounterAudioProcessor::getNumPrograms()
{
    return 0;
}

int BeatCounterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BeatCounterAudioProcessor::setCurrentProgram (int index)
{
}

const String BeatCounterAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void BeatCounterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BeatCounterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BeatCounterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void BeatCounterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);

        // ..do something to the data...
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool BeatCounterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BeatCounterAudioProcessor::createEditor()
{
    return new BeatCounterAudioProcessorEditor (this);
}

//==============================================================================
void BeatCounterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BeatCounterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BeatCounterAudioProcessor();
}
