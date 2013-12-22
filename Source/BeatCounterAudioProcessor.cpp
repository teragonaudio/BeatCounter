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
BeatCounterAudioProcessor::BeatCounterAudioProcessor() : AudioProcessor()
{
    parameters.add(new IntegerParameter("Tolerance", kParamToleranceMinValue, kParamToleranceMaxValue, kParamToleranceDefaultValue));
    parameters["Tolerance"]->addObserver(this);
    parameters.add(new FloatParameter("Period", kParamPeriodMinValue, kParamPeriodMaxValue, kParamPeriodDefaultValue));
    parameters["Period"]->addObserver(this);
    parameters.add(new BooleanParameter("Filter", true));
    parameters["Filter"]->addObserver(this);
    parameters.add(new FrequencyParameter("Filter Frequency", kParamFilterMinValue, kParamFilterMaxValue, kParamFilterDefaultValue));
    parameters["Filter Frequency"]->addObserver(this);
    parameters.add(new BooleanParameter("Use Host Tempo", false));
    parameters["Use Host Tempo"]->addObserver(this);
    parameters.add(new VoidParameter("Reset"));
    parameters["Reset"]->addObserver(this);

    parameters.add(new VoidParameter("Beat Triggered"));
    parameters.add(new FloatParameter("Current BPM", kMinimumTempo, kMaximumTempo, kDefaultTempo));
    parameters.add(new FloatParameter("Running BPM", kMinimumTempo, kMaximumTempo, kDefaultTempo));
    reset();
}

int BeatCounterAudioProcessor::getNumParameters() {
    return parameters.size();
}

float BeatCounterAudioProcessor::getParameter(int index) {
    return (float)parameters[index]->getScaledValue();
}

void BeatCounterAudioProcessor::setParameter(int index, float newValue) {
    parameters.setScaled(index, newValue);
}

const String BeatCounterAudioProcessor::getParameterName(int index) {
    return parameters[index]->getName();
}

const String BeatCounterAudioProcessor::getParameterText(int index) {
    return parameters[index]->getDisplayText();
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

void BeatCounterAudioProcessor::reset()
{
    bpmHistory.clear();
    filterOutput = 0.0f;
    filterConstant = calculateFilterConstant(getSampleRate(), filterFrequency);
    numSamplesProcessed = 0;
    highestAmplitude = 0.0;
    highestAmplitudeInPeriod = 0.0;
    currentlyInsideBeat = false;
    beatLengthRunningAverage = 0;
    numSamplesSinceLastBeat = 0;
    currentBpm = 0.0;
    runningBpm = 0.0;
}

void BeatCounterAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
    parameters.processRealtimeEvents();

    for(int i = 0; i < buffer.getNumSamples(); ++i) {
        float currentSample = *buffer.getSampleData(0, i);
        double currentSampleAmplitude;

        if(filterEnabled) {
            // This relies on the sample rate which may not be available during initialization
            if(filterConstant == 0.0) {
                filterConstant = calculateFilterConstant(getSampleRate(), filterFrequency);
            }
            // Basic lowpass filter (feedback)
            filterOutput += (currentSample - filterOutput) / filterConstant;
            currentSampleAmplitude = fabs(filterOutput);
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

                        parameters.set("Beat Triggered", 1.0f);
                        parameters.set("Current BPM", currentBpm);

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
                            parameters.set("Running BPM", runningBpm);
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

void BeatCounterAudioProcessor::onParameterUpdated(const PluginParameter *parameter) {
    if(parameter->getName() == "Reset") {
        reset();
    }
    else if(parameter->getName() == "Filter") {
        filterEnabled = parameter->getValue() > 0.5;
    }
    else if(parameter->getName() == "Tolerance") {
        tolerance = parameter->getValue();
    }
    else if(parameter->getName() == "Filter Frequency") {
        filterFrequency = parameter->getValue();
        // Yeah, you'd think that it would make sense to cache these values here, given that it's
        // just the period size * sample rate, however the sample rate isn't necessarily available
        // to the plugin unless playback has started (and afterwards, it is guaranteed not to change
        // until playback stops). So this must instead be cached and calculated in processBlock().
        // So instead we just set their values to 0, which will force processBlock() to recalculate
        // them. Same goes for the period size below.
        filterConstant = 0.0;
    }
    else if(parameter->getName() == "Use Host Tempo") {
        linkWithHostTempo = parameter->getValue() > 0.5;
    }
    else if(parameter->getName() == "Period") {
        periodSizeInSeconds = parameters["Period"]->getValue();
        periodSizeInSamples = 0;
    }
}

double BeatCounterAudioProcessor::calculateFilterConstant(double sampleRate, double frequency) const
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
    for (int i = 0; i < parameters.size(); ++i) {
        PluginParameter* parameter = parameters[i];
        xml.setAttribute(parameter->getSafeName().c_str(), parameter->getValue());
    }
    copyXmlToBinary(xml, destData);
}

void BeatCounterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != 0 && xmlState->hasTagName(kStorageName)) {
        for(int i = 0; i < parameters.size(); i++) {
            PluginParameter* parameter = parameters[i];
            parameters.set(parameter, xmlState->getDoubleAttribute(parameter->getSafeName().c_str()));
        }
        reset();
    }
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BeatCounterAudioProcessor();
}

AudioProcessorEditor* BeatCounterAudioProcessor::createEditor()
{
    return new MainEditorView(this, parameters, Resources::getCache());
}
