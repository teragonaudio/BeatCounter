/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

#if WIN32
// Needed for M_PI on Windows
#define _USE_MATH_DEFINES
#include <math.h>
#endif

BeatCounterAudioProcessor::BeatCounterAudioProcessor() : TeragonPluginBase(), ParameterObserver() {
    tolerance = new IntegerParameter("Tolerance", kParamToleranceMinValue, kParamToleranceMaxValue, kParamToleranceDefaultValue);
    tolerance->setUnit("%");
    parameters.add(tolerance);

    period = new FloatParameter("Period", kParamPeriodMinValue, kParamPeriodMaxValue, kParamPeriodDefaultValue);
    period->setUnit("sec");
    parameters.add(period);

    filterEnabled = new BooleanParameter("Filter", true);
    parameters.add(filterEnabled);

    filterFrequency = new FrequencyParameter("Filter Frequency", kParamFilterMinValue, kParamFilterMaxValue, kParamFilterDefaultValue);
    filterFrequency->addObserver(this);
    parameters.add(filterFrequency);

    useHostTempo = new BooleanParameter("Use Host Tempo", false);
    parameters.add(useHostTempo);

    parameters.add(new VoidParameter("Reset"));
    parameters["Reset"]->addObserver(this);

    parameters.add(new VoidParameter("Beat Triggered"));
    parameters.add(new FloatParameter("Current BPM", kMinimumTempo, kMaximumTempo, kDefaultTempo));
    parameters.add(new FloatParameter("Running BPM", kMinimumTempo, kMaximumTempo, kDefaultTempo));

    ParameterString version = ProjectInfo::projectName;
    version.append(" verison ").append(ProjectInfo::versionString);
    parameters.add(new StringParameter("Version", version));

    parameters.pause();
}

void BeatCounterAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    TeragonPluginBase::prepareToPlay(sampleRate, samplesPerBlock);
    minimumAllowedBpm = kMinimumTempo;
    maximumAllowedBpm = kMaximumTempo;
    cooldownPeriodInSamples = (unsigned long)(sampleRate * (60.0f / (float)maximumAllowedBpm));
    samplesToSkip = kDownsampleFactor;
    clearBpmHistory();
}

void BeatCounterAudioProcessor::clearBpmHistory() {
    bpmHistory.clear();
    filterOutput = 0.0f;
    numSamplesProcessed = 0;
    highestAmplitude = 0.0;
    highestAmplitudeInPeriod = 0.0;
    currentlyInsideBeat = false;
    beatLengthRunningAverage = 0;
    numSamplesSinceLastBeat = 0;
    parameters.set("Current BPM", 0.0);
    parameters.set("Running BPM", 0.0);
    runningBpm = 0.0;
}

void BeatCounterAudioProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {
    TeragonPluginBase::processBlock(buffer, midiMessages);

    for(int i = 0; i < buffer.getNumSamples(); ++i) {
        float currentSample = *buffer.getSampleData(0, i);
        double currentSampleAmplitude;

        if(filterEnabled) {
            // This relies on the sample rate which may not be available during initialization
            if(filterConstant == 0.0) {
                filterConstant = calculateFilterConstant(getSampleRate(), filterFrequency->getValue());
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
            if(highestAmplitudeInPeriod >= (highestAmplitude * tolerance->getValue() / 100.0) &&
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
                        bpmHistory.push_back(bpm);
                        parameters.set("Beat Triggered", 1.0f);
                        parameters.set("Current BPM", bpm);

                        // Do total BPM and Reset?
                        if(numSamplesProcessed > period->getValue() * getSampleRate()) {
                            // Take advantage of this trigger point to do a tempo check and adjust the minimum
                            // and maximum BPM ranges accordingly.
                            if(useHostTempo->getValue()) {
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

void BeatCounterAudioProcessor::releaseResources() {
    TeragonPluginBase::releaseResources();
    clearBpmHistory();
}

void BeatCounterAudioProcessor::onParameterUpdated(const Parameter *parameter) {
    if(parameter->getName() == "Reset") {
        clearBpmHistory();
    }
    else if(parameter->getName() == "Filter Frequency") {
        // Yeah, you'd think that it would make sense to cache these values here, given that it's
        // just the period size * sample rate, however the sample rate isn't necessarily available
        // to the plugin unless playback has started (and afterwards, it is guaranteed not to change
        // until playback stops). So this must instead be cached and calculated in processBlock().
        // So instead we just set their values to 0, which will force processBlock() to recalculate
        // them.
        filterConstant = 0.0;
    }
}

double BeatCounterAudioProcessor::calculateFilterConstant(double sampleRate, double frequency) const {
    return sampleRate / (2.0f * M_PI * frequency);
}

double BeatCounterAudioProcessor::getHostTempo() const {
    double result = kDefaultTempo;

    AudioPlayHead *playHead = getPlayHead();
    if(playHead != NULL) {
        AudioPlayHead::CurrentPositionInfo currentPosition;
        playHead->getCurrentPosition(currentPosition);
        result = currentPosition.bpm;
    }

    return result;
}

AudioProcessorEditor *BeatCounterAudioProcessor::createEditor() {
    return new MainEditorView(this, parameters, Resources::getCache());
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new BeatCounterAudioProcessor();
}
