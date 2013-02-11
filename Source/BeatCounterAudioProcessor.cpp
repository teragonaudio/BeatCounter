/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "BeatCounterAudioProcessor.h"
#include "MainEditorView.h"

//==============================================================================
BeatCounterAudioProcessor::BeatCounterAudioProcessor()
{
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
    return (float const)(log(rawValue) - log(minValue)) / (log(maxValue) - log(minValue));
}

//==============================================================================
float BeatCounterAudioProcessor::getParameter (int index)
{
    switch (index) {
        case kParamReset:
            break;
        case kParamTolerance:
            return getParameterScaled((float) tolerance, kParamToleranceMinValue, kParamToleranceMaxValue);
        case kParamPeriod:
            return getParameterScaled((float) (periodSizeInSamples / getSampleRate()), kParamPeriodMinValue, kParamPeriodMaxValue);
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
        {
            double periodSizeInSeconds = 0.0;
            setParameterScaled(&periodSizeInSeconds, newValue, kParamToleranceMinValue, kParamToleranceMaxValue);
            periodSizeInSamples = (unsigned long) (periodSizeInSeconds * getSampleRate());
        }
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
            return String::formatted("%.1f", periodSizeInSamples / getSampleRate());
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
    m_min_bpm = kMinimumTempo;
    m_max_bpm = kMaximumTempo;
    m_dupe_interval = (unsigned long)(sampleRate * (60.0f / (float)m_max_bpm));
    m_downsample_rate = kDownsampleRate;
    m_skip_count = m_downsample_rate;
    m_downsampled = new double[(int)((sampleRate * 20) / m_downsample_rate)];
    this->currentBpm = 0.0f;
    this->runningBpm = 0.0f;
}

void BeatCounterAudioProcessor::releaseResources()
{
}

void BeatCounterAudioProcessor::reset()
{
    bpmHistory.clear();
}

void BeatCounterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    for(int i = 0; i < buffer.getNumSamples(); ++i) {
        float* currentSample = buffer.getSampleData(0, i);
        double currentSampleAmplitude = 0.0f;

        if(this->isAutofilterEnabled) {
            // Basic lowpass filter (feedback)
            this->autofilterOutput += (*currentSample - this->autofilterOutput) / this->autofilterConstant;
            currentSampleAmplitude = fabs(this->autofilterOutput);
        }
        else {
            currentSampleAmplitude = fabs(*currentSample);
        }

        // Find highest peak in downsampled area ("bar")
        if(*currentSample > m_bar_high_point) {
            m_bar_high_point = *currentSample;

            // Find highest averaging value for testing period
            if(*currentSample > m_high_point) {
                m_high_point = *currentSample;
            }
        }

        // Process one "bar"
        if(--m_skip_count <= 0) {
            // Calculate average point
            m_bar_samp_avg /= m_downsample_rate;

            // Beat amplitude/frequency has been detected
            if(m_bar_samp_avg >= (m_bar_high_avg * this->tolerance / 100.0) &&
                    m_bar_high_point >= (m_high_point * this->tolerance / 100.0) &&
                    m_bar_high_point > kSilenceThreshold) {

                // First bar in a beat?
                if(!beatState && m_beat_samples > m_dupe_interval) {
                    beatState = true;
                    double bpm = (getSampleRate() * 60.0f) / ((m_last_avg + m_beat_samples) / 2);

                    // Check for half-beat patterns
                    double hbpm = bpm * 2.0;
                    if(hbpm > m_min_bpm && hbpm < m_max_bpm) {
                        bpm = hbpm;
                    }

                    // See if we're inside the threshhold
                    if(bpm > m_min_bpm && bpm < m_max_bpm) {
                        this->currentBpm = bpm;

                        m_last_avg += m_beat_samples;
                        m_last_avg /= 2;
                        m_beat_samples = 0;
                        bpmHistory.push_back(bpm);

                        // Do total BPM and Reset?
                        if(m_num_samples_processed > (this->periodSizeInSamples * getSampleRate())) {
                            // Take advantage of this trigger point to do a tempo check
                            if(this->linkWithHostTempo) {
                                m_min_bpm = getHostTempo() - kHostTempoLinkToleranceInBpm;
                                m_max_bpm = getHostTempo() + kHostTempoLinkToleranceInBpm;
                                m_dupe_interval = (unsigned long)(getSampleRate() * (60.0f / (float)m_max_bpm));
                            }

                            this->runningBpm = 0.0;
                            for(unsigned int bpmHistoryIndex = 0; bpmHistoryIndex < bpmHistory.size(); ++bpmHistoryIndex) {
                                this->runningBpm += bpmHistory.at(bpmHistoryIndex);
                            }
                            bpmHistory.clear();
                            m_num_samples_processed = 0;
                        }
                    }
                    else {
                        // Outside of bpm threshhold
                        // TODO: Unset BPM Display in GUI
                        m_last_avg += m_beat_samples;
                        m_last_avg /= 2;
                        m_beat_samples = 0;
                    }
                }
                else {
                    // Not the first beat mark
                    beatState = false;
                }
            }
            else {
                // Were we just in a beat?
                if(beatState) {
                    beatState = false;
                }
            }

            m_skip_count = m_downsample_rate;
            m_bar_high_point = 0.0;
            m_bar_samp_avg = 0.0;
        }
        else {
            m_bar_samp_avg += *currentSample;
        }

        ++m_num_samples_processed;
        ++m_beat_samples;
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
    XmlElement xml("BeatCounterStorage");
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
  if(xmlState != 0 && xmlState->hasTagName("BeatCounterStorage")) {
    for(int i = 0; i < kNumParams; i++) {
      if(isParameterStored(i)) {
        setParameter(i, xmlState->getDoubleAttribute(getParameterNameForStorage(i)));
      }
    }
  }
}

//==============================================================================
const double BeatCounterAudioProcessor::getCurrentBpm() const
{
    return this->currentBpm;
}

const double BeatCounterAudioProcessor::getRunningBpm() const
{
    return this->runningBpm;
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
    MainEditorView* editorView = new MainEditorView(this);
    editorView->setViewController(this);
    return editorView;
}
