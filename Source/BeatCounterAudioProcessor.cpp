/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "BeatCounterAudioProcessor.h"
#include "MainEditorView.h"

static char const *const kStorageName = "BeatCounterStorage";

//==============================================================================
BeatCounterAudioProcessor::BeatCounterAudioProcessor() : AudioProcessor(), EditorViewController()
{
    tolerance = kParamToleranceDefaultValue;
    periodSizeInSeconds = kParamPeriodDefaultValue;
    periodSizeInSamples = 0;
    autofilterEnabled = false;
    autofilterFrequency = kParamAutofilterDefaultValue;
    linkWithHostTempo = false;
    reset();
}

BeatCounterAudioProcessor::~BeatCounterAudioProcessor()
{
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
        case kParamReset:
            break;
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
        case kParamReset:
            if (newValue > 0.5f) {
                reset();
            }
            break;
        case kParamTolerance:
            setParameterScaled(&tolerance, newValue, kParamToleranceMinValue, kParamToleranceMaxValue);
            break;
        case kParamPeriod:
            setParameterScaled(&periodSizeInSeconds, newValue, kParamPeriodMinValue, kParamPeriodMaxValue);
            periodSizeInSamples = 0;
            break;
        case kParamAutofilterEnabled:
            autofilterEnabled = (newValue > 0.5f);
            break;
        case kParamAutofilterFrequency:
            setParameterFrequency(&autofilterFrequency, newValue, kParamAutofilterMinValue, kParamAutofilterMaxValue);
            autofilterConstant = calculateAutofilterConstant(getSampleRate(), autofilterFrequency);
            break;
        case kParamLinkToHostTempo:
            linkWithHostTempo = (newValue > 0.5f);
            break;
        default:
            break;
    }
}

String BeatCounterAudioProcessor::getParameterNameForStorage(int index) const
{
    switch (index) {
        case kParamReset:
            return "Reset";
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
        case kParamReset:
            return "Reset";
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
        case kParamReset:
            return String::empty;
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
        case kParamReset:
            return false;
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
    totalRunningAmplitude = 0.0;
    currentlyInsideBeat = false;
    beatLengthRunningAverage = 0;
    numSamplesSinceLastBeat = 0;
    currentBpm = 0.0;
    runningBpm = 0.0;
}

void BeatCounterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    for(int i = 0; i < buffer.getNumSamples(); ++i) {
        float currentSample = *buffer.getSampleData(0, i);
        double currentSampleAmplitude;

        if(autofilterEnabled) {
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
            // Calculate average point
            totalRunningAmplitude /= kDownsampleFactor;

            // Beat amplitude/frequency has been detected
            if(totalRunningAmplitude >= (0.0f * tolerance / 100.0) &&
                    highestAmplitudeInPeriod >= (highestAmplitude * tolerance / 100.0) &&
                    highestAmplitudeInPeriod > kSilenceThreshold) {

                // First bar in a beat?
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
                        // TODO: Turn on beat light in GUI
                        currentBpm = bpm;
                        bpmHistory.push_back(bpm);

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
                        }
                    }
                    else {
                        // Outside of bpm threshhold
                        // TODO: Unset BPM Display in GUI
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
            totalRunningAmplitude = 0.0;
        }
        else {
            totalRunningAmplitude += currentSampleAmplitude;
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
    if(playHead != NULL) {
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
const double BeatCounterAudioProcessor::getCurrentBpm() const
{
    return currentBpm;
}

const double BeatCounterAudioProcessor::getRunningBpm() const
{
    return runningBpm;
}

const bool BeatCounterAudioProcessor::isBeatActive() const
{
    return currentlyInsideBeat;
}

void BeatCounterAudioProcessor::onFilterButtonPressed(bool isEnabled)
{
    setParameter(kParamAutofilterEnabled, isEnabled ? 1.0 : 0.0);
}

void BeatCounterAudioProcessor::onLinkButtonPressed(bool isEnabled)
{
    setParameter(kParamLinkToHostTempo, isEnabled ? 1.0 : 0.0);
}

void BeatCounterAudioProcessor::onResetButtonPressed(bool isEnabled)
{
    reset();
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
    editorView->setViewController(this);
    return editorView;
}
