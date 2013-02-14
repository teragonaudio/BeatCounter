/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "BeatCounterAudioProcessor.h"
#include "MainEditorView.h"
#ifdef WIN32
#define _USE_MATH_DEFINES 1
#include <math.h>
#endif

static char const *const kStorageName = "BeatCounterStorage";

//==============================================================================
BeatCounterAudioProcessor::BeatCounterAudioProcessor() : AudioProcessor(), EditorViewController()
{
    editor = nullptr;

    tolerance = kParamToleranceDefaultValue;
    periodSizeInSeconds = kParamPeriodDefaultValue;
    periodSizeInSamples = 0;
    autofilterEnabled = true;
    autofilterFrequency = kParamAutofilterDefaultValue;
    linkWithHostTempo = false;

    virtualMidiOutput = nullptr;
    virtualMidiOutputEnabled = true;
    sendMidiNotes = true;
    sendMidiClock = true;

    reset();
}

BeatCounterAudioProcessor::~BeatCounterAudioProcessor()
{
    if(virtualMidiOutput) {
        virtualMidiOutput->clearAllPendingMessages();
        virtualMidiOutput->stopBackgroundThread();
        delete virtualMidiOutput;
        virtualMidiOutput = nullptr;
    }
}

float BeatCounterAudioProcessor::getParameterScaled (float rawValue, float minValue, float maxValue) const
{
    return (rawValue - minValue) / (maxValue - minValue);
}

float BeatCounterAudioProcessor::getParameterFrequency (double rawValue, float minValue, float maxValue) const
{
    return (float const)((log(rawValue) - log(minValue)) / (log(maxValue) - log(minValue)));
}

//==============================================================================
float BeatCounterAudioProcessor::getParameter (int index)
{
    switch (index) {
        case kParamTolerance:
            return getParameterScaled((float)tolerance, kParamToleranceMinValue, kParamToleranceMaxValue);
        case kParamPeriod:
            return getParameterScaled((float)periodSizeInSeconds, kParamPeriodMinValue, kParamPeriodMaxValue);
        case kParamAutofilterEnabled:
            return autofilterEnabled ? 1.0f : 0.0f;
        case kParamAutofilterFrequency:
            return getParameterFrequency(autofilterFrequency, kParamAutofilterMinValue, kParamAutofilterMaxValue);
        case kParamLinkToHostTempo:
            return linkWithHostTempo ? 1.0f : 0.0f;
        default:
            break;
    }

    // Only reached for special parameters
    return 0.0f;
}

void BeatCounterAudioProcessor::setParameterScaled(double *destination, float scaledValue, float minValue, float maxValue)
{
    *destination = scaledValue * (maxValue - minValue) + minValue;
}

void BeatCounterAudioProcessor::setParameterFrequency(double *destination, float scaledValue, float minValue, float maxValue)
{
    *destination = exp(scaledValue * (log(maxValue) - log(minValue)) + log(minValue));
}

void BeatCounterAudioProcessor::setParameter (int index, float newValue)
{
    switch (index) {
        case kParamTolerance:
            setParameterScaled(&tolerance, newValue, kParamToleranceMinValue, kParamToleranceMaxValue);
            if(editor) {
                editor->updateParameter(kParamTolerance, tolerance);
            }
            break;
        case kParamPeriod:
            setParameterScaled(&periodSizeInSeconds, newValue, kParamPeriodMinValue, kParamPeriodMaxValue);
            periodSizeInSamples = 0;
            break;
        case kParamAutofilterEnabled:
            autofilterEnabled = (newValue > 0.5f);
            if(editor) {
                editor->updateParameter(kParamAutofilterEnabled, autofilterEnabled ? 1.0 : 0.0);
            }
            break;
        case kParamAutofilterFrequency:
            setParameterFrequency(&autofilterFrequency, newValue, kParamAutofilterMinValue, kParamAutofilterMaxValue);
            autofilterConstant = 0.0;
            if(editor) {
                editor->updateParameter(kParamAutofilterFrequency, autofilterFrequency);
            }
            break;
        case kParamLinkToHostTempo:
            linkWithHostTempo = (newValue > 0.5f);
            if(editor) {
                editor->updateParameter(kParamLinkToHostTempo, linkWithHostTempo ? 1.0 : 0.0);
            }
            break;
        default:
            break;
    }
}

String BeatCounterAudioProcessor::getParameterNameForStorage(int index) const
{
    switch (index) {
        case kParamTolerance:
            return "Tolerance";
        case kParamPeriod:
            return "Period";
        case kParamAutofilterEnabled:
            return "AutofilterOn";
        case kParamAutofilterFrequency:
            return "AutofilterFrequency";
        case kParamLinkToHostTempo:
            return "LinkHostTempo";
        default:
            return String::empty;
    }
}

const String BeatCounterAudioProcessor::getParameterName (int index)
{
    switch (index) {
        case kParamTolerance:
            return "Tolerance";
        case kParamPeriod:
            return "Period";
        case kParamAutofilterEnabled:
            return "Autofilter On";
        case kParamAutofilterFrequency:
            return "Autofilter Frequency";
        case kParamLinkToHostTempo:
            return "Link to Host Tempo";
        default:
            return String::empty;
    }
}

const String BeatCounterAudioProcessor::getParameterText (int index)
{
    switch (index) {
        case kParamTolerance:
            return String::formatted("%.0f", tolerance);
        case kParamPeriod:
            return String::formatted("%.1f", periodSizeInSeconds);
        case kParamAutofilterEnabled:
            return autofilterEnabled ? "On" : "Off";
        case kParamAutofilterFrequency:
            return String::formatted("%.2f", autofilterFrequency);
        case kParamLinkToHostTempo:
            return linkWithHostTempo ? "On" : "Off";
        default:
            return String::empty;
    }
}

bool BeatCounterAudioProcessor::isParameterStored(int index) const
{
    switch (index) {
        case kParamTolerance:
            return true;
        case kParamPeriod:
            return true;
        case kParamAutofilterEnabled:
            return true;
        case kParamAutofilterFrequency:
            return true;
        case kParamLinkToHostTempo:
            return true;
        default:
            return false;
    }
}

//==============================================================================
void BeatCounterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    minimumAllowedBpm = kMinimumTempo;
    maximumAllowedBpm = kMaximumTempo;
    cooldownPeriodInSamples = (unsigned long)(sampleRate * (60.0f / (float) maximumAllowedBpm));
    samplesToSkip = kDownsampleFactor;
    currentBpm = 0.0f;
    runningBpm = 0.0f;

    if(virtualMidiOutputEnabled && virtualMidiOutput == nullptr) {
        virtualMidiOutput = MidiOutput::createNewDevice(getName());
        if(virtualMidiOutput) {
            virtualMidiOutput->startBackgroundThread();
        }
    }
}

void BeatCounterAudioProcessor::releaseResources()
{
}

void BeatCounterAudioProcessor::reset()
{
    bpmHistory.clear();
    autofilterOutput = 0.0f;
    autofilterConstant = calculateAutofilterConstant(getSampleRate(), autofilterFrequency);
    numSamplesProcessed = 0;
    highestAmplitude = 0.0;
    highestAmplitudeInPeriod = 0.0;
    currentlyInsideBeat = false;
    beatLengthRunningAverage = 0;
    numSamplesSinceLastBeat = 0;
    currentBpm = 0.0;
    runningBpm = 0.0;

    if (virtualMidiOutput) {
        virtualMidiOutput->clearAllPendingMessages();
    }

    if(editor) {
        editor->updateCurrentBpm(currentBpm);
        editor->updateRunningBpm(runningBpm);
    }
}

void BeatCounterAudioProcessor::onBeatDetected() const {
    if(editor) {
        editor->triggerBeatLight();
        editor->updateCurrentBpm(currentBpm);
    }

    if(virtualMidiOutput) {
        if(sendMidiNotes) {
            // Middle C, maximum velocity
            MidiMessage noteOn(0x90, 0x3c, 0x7f);
            virtualMidiOutput->sendMessageNow(noteOn);
            MidiMessage noteOff(0x80, 0x3c, 0x00, 1000);
            virtualMidiOutput->sendMessageNow(noteOff);
        }
        if(sendMidiClock) {
            // TODO
        }
    }
}

void BeatCounterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    for(int i = 0; i < buffer.getNumSamples(); ++i) {
        float currentSample = *buffer.getSampleData(0, i);
        double currentSampleAmplitude;

        if(autofilterEnabled) {
            // This relies on the sample rate which may not be available during initialization
            if(autofilterConstant == 0.0) {
                autofilterConstant = calculateAutofilterConstant(getSampleRate(), autofilterFrequency);
            }
            // Basic lowpass filter (feedback)
            autofilterOutput += (currentSample - autofilterOutput) / autofilterConstant;
            currentSampleAmplitude = fabs(autofilterOutput);
        }
        else {
            currentSampleAmplitude = fabs(currentSample);
        }

        // Find highest peak in the current period
        if(currentSampleAmplitude > highestAmplitudeInPeriod) {
            highestAmplitudeInPeriod = currentSampleAmplitude;

            // Is it also the highest value since we started?
            if(currentSampleAmplitude > highestAmplitude) {
                highestAmplitude = currentSampleAmplitude;
            }
        }

        // Downsample by skipping samples
        if(--samplesToSkip <= 0) {

            // Beat amplitude trigger has been detected
            if(highestAmplitudeInPeriod >= (highestAmplitude * tolerance / 100.0) &&
                    highestAmplitudeInPeriod > kSilenceThreshold) {

                // First sample inside of a beat?
                if(!currentlyInsideBeat && numSamplesSinceLastBeat > cooldownPeriodInSamples) {
                    currentlyInsideBeat = true;
                    double bpm = (getSampleRate() * 60.0f) / ((beatLengthRunningAverage + numSamplesSinceLastBeat) / 2);

                    // Check for half-beat patterns. For instance, a song which has a kick drum
                    // at around 70 BPM but an actual tempo of 140 BPM (hello, dubstep!).
                    double doubledBpm = bpm * 2.0;
                    if(doubledBpm > minimumAllowedBpm && doubledBpm < maximumAllowedBpm) {
                        bpm = doubledBpm;
                    }

                    beatLengthRunningAverage += numSamplesSinceLastBeat;
                    beatLengthRunningAverage /= 2;
                    numSamplesSinceLastBeat = 0;

                    // Check to see that this tempo is within the limits allowed
                    if(bpm > minimumAllowedBpm && bpm < maximumAllowedBpm) {
                        currentBpm = bpm;
                        bpmHistory.push_back(bpm);
                        onBeatDetected();

                        // The sample rate is not known when a JUCE plugin is initialized, so grab it lazily here
                        if(periodSizeInSamples == 0) {
                            periodSizeInSamples = (unsigned long)(periodSizeInSeconds * getSampleRate());
                        }

                        // Do total BPM and Reset?
                        if(numSamplesProcessed > periodSizeInSamples) {
                            // Take advantage of this trigger point to do a tempo check and adjust the minimum
                            // and maximum BPM ranges accordingly.
                            if(linkWithHostTempo) {
                                minimumAllowedBpm = getHostTempo() - kHostTempoLinkToleranceInBpm;
                                maximumAllowedBpm = getHostTempo() + kHostTempoLinkToleranceInBpm;
                                cooldownPeriodInSamples = (unsigned long)(getSampleRate() * (60.0 / maximumAllowedBpm));
                            }

                            runningBpm = 0.0;
                            for(unsigned int historyIndex = 0; historyIndex < bpmHistory.size(); ++historyIndex) {
                                runningBpm += bpmHistory.at(historyIndex);
                            }
                            runningBpm /= (double)bpmHistory.size();
                            bpmHistory.clear();
                            numSamplesProcessed = 0;
                            if(editor) {
                                editor->updateRunningBpm(runningBpm);
                            }
                        }
                    }
                    else {
                        // Outside of bpm threshold, ignore
                    }
                }
                else {
                    // Not the first beat mark
                    currentlyInsideBeat = false;
                }
            }
            else {
                // Were we just in a beat?
                if(currentlyInsideBeat) {
                    currentlyInsideBeat = false;
                }
            }

            samplesToSkip = kDownsampleFactor;
            highestAmplitudeInPeriod = 0.0;
        }

        ++numSamplesProcessed;
        ++numSamplesSinceLastBeat;
    }
}

double BeatCounterAudioProcessor::calculateAutofilterConstant(double sampleRate, double frequency) const
{
    return sampleRate / (2.0f * M_PI * frequency);
}

double BeatCounterAudioProcessor::getHostTempo() const
{
    double result = kDefaultTempo;

    AudioPlayHead* playHead = getPlayHead();
    if(playHead) {
        AudioPlayHead::CurrentPositionInfo currentPosition;
        playHead->getCurrentPosition(currentPosition);
        result = currentPosition.bpm;
    }

    return result;
}

//==============================================================================
void BeatCounterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml(kStorageName);
    for (int i = 0; i < kNumParams; ++i) {
        if (isParameterStored(i)) {
            xml.setAttribute(getParameterNameForStorage(i), (double)getParameter(i));
        }
    }
    copyXmlToBinary(xml, destData);
}

void BeatCounterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != 0 && xmlState->hasTagName(kStorageName)) {
        for (int i = 0; i < kNumParams; i++) {
            if (isParameterStored(i)) {
                setParameter(i, (float) xmlState->getDoubleAttribute(getParameterNameForStorage(i)));
            }
        }
        reset();
    }
}

//==============================================================================
void BeatCounterAudioProcessor::onToleranceChanged(double value)
{
    tolerance = value;
}

void BeatCounterAudioProcessor::onFilterButtonPressed(bool isEnabled)
{
    setParameter(kParamAutofilterEnabled, isEnabled ? 1.0 : 0.0);
}

void BeatCounterAudioProcessor::onFilterFrequencyChanged(double value)
{
    autofilterFrequency = value;
    autofilterConstant = 0.0;
}

void BeatCounterAudioProcessor::onLinkButtonPressed(bool isEnabled)
{
    setParameter(kParamLinkToHostTempo, isEnabled ? 1.0 : 0.0);
}

void BeatCounterAudioProcessor::onResetButtonPressed(bool isEnabled)
{
    reset();
}

bool BeatCounterAudioProcessor::getLinkButtonState() const {
    return linkWithHostTempo;
}

bool BeatCounterAudioProcessor::getFilterButtonState() const {
    return autofilterEnabled;
}

void BeatCounterAudioProcessor::onEditorClosed() {
    editor = nullptr;
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BeatCounterAudioProcessor();
}

AudioProcessorEditor* BeatCounterAudioProcessor::createEditor()
{
    MainEditorView *editorView = new MainEditorView(this);
    editor = editorView;
    editorView->setViewController(this);
    editor->updateParameter(kParamTolerance, tolerance);
    editor->updateParameter(kParamAutofilterEnabled, autofilterEnabled ? 1.0 : 0.0);
    editor->updateParameter(kParamAutofilterFrequency, autofilterFrequency);
    editor->updateParameter(kParamLinkToHostTempo, linkWithHostTempo ? 1.0 : 0.0);
    return editorView;
}
