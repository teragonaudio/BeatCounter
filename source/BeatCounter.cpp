/*
 *  BeatCounter - BeatCounter.cpp
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __BeatCounter_h__
#include "BeatCounter.h"
#endif

#ifndef __BeatCounterEditor_h__
#include "BeatCounterEditor.h"
#endif

#include <math.h>

AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new teragon::BeatCounter();
}

namespace teragon {
  BeatCounter::BeatCounter() : AudioProcessor() {
    this->autofilterEnabled = false;
    this->autofilterFrequency = kMaxAutofilterFrequency;

    reset();
  }

  BeatCounter::~BeatCounter() {
  }

  const String BeatCounter::getParameterName(int parameterIndex) {
    switch(parameterIndex) {
      case kParamReset: return "Reset";
      case kParamTolerance: return "Tolerance";
      case kParamPeriod: return "Period";
      case kParamAutofilterEnabled: return "Autofilter Enabled";
      case kParamAutofilterFrequency: return "Autofilter Frequency";
      case kParamLinkToHostTempo: return "Link to Host Tempo";
      default: return String::empty;
    }
  }

  float BeatCounter::getParameter(int parameterIndex) {
    return 0.0f;
  }

  const String BeatCounter::getParameterText(int parameterIndex) {
    return String::empty;
  }

  void BeatCounter::setParameter(int parameterIndex, float newValue) {
  }

  void BeatCounter::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {
    m_min_bpm = kMinimumTempo;
    m_max_bpm = kMaximumTempo;
    m_dupe_interval = (long)(44100 * (float)(60.0f / (float)m_max_bpm));  
    m_downsample_rate = kDownsampleRate;
    m_skip_count = m_downsample_rate;
    m_downsampled = new double[(int)((44100 * 20) / m_downsample_rate)];
    this->currentBpm = 0.0f;
    this->runningBpm = 0.0f;
  }

  void BeatCounter::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
    for(int i = 0; i < buffer.getNumSamples(); ++i) {
      float* currentSample = buffer.getSampleData(0, i);
      double currentSampleAmplitude = 0.0f;

      if(this->autofilterEnabled) {
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
          if(!m_beat_state && m_beat_samples > m_dupe_interval) {
            m_beat_state = true;
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
              m_bpm_history.push_back(bpm);
              
              // Do total BPM and Reset?
              if(m_num_samples_processed > (this->periodSizeInSamples * getSampleRate())) {
                // Take advantage of this trigger point to do a tempo check
                if(this->linkWithHostTempo) {
                  m_min_bpm = getHostTempo() - kHostTempoLinkToleranceInBpm;
                  m_max_bpm = getHostTempo() + kHostTempoLinkToleranceInBpm;
                  m_dupe_interval = (long)(getSampleRate() * (float)(60.0f / (float)m_max_bpm));
                }
                
                this->runningBpm = 0.0;
                unsigned int i;
                for(i = 0; i < m_bpm_history.size(); ++i) {
                  this->runningBpm += m_bpm_history.at(i);
                }
                m_bpm_history.clear();
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
            m_beat_state = false;
          }
        }
        else {
          // Were we just in a beat?
          if(m_beat_state) {
            m_beat_state = false;
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

  double BeatCounter::getHostTempo() const {
    double result = kDefaultTempo;
    
    AudioPlayHead* playHead = getPlayHead();
    if(playHead != NULL) {
      AudioPlayHead::CurrentPositionInfo currentPosition;
      playHead->getCurrentPosition(currentPosition);
      result = currentPosition.bpm;
    }
    
    return result;
  }
  
  void BeatCounter::releaseResources() {
  }

  void BeatCounter::reset() {
    this->autofilterOutput = 0.0f;
    this->autofilterConstant = calculateAutofilterConstant(getSampleRate(), this->autofilterFrequency);
  }

  double BeatCounter::calculateAutofilterConstant(double sampleRate, double frequency) const {
    return sampleRate / (2.0f * M_PI * frequency);
  }

  AudioProcessorEditor* BeatCounter::createEditor() {
    return new BeatCounterEditor(this);
  }
  
  const float BeatCounter::getCurrentBpm() const {
    return this->currentBpm;
  }
  
  const float BeatCounter::getRunningBpm() const {
    return this->runningBpm;
  }
}

/*
BeatCounterCore::BeatCounterCore(int num_params, int version, char *name) : pluginCore(num_params, VERSION, name) {
  init();
}

void BeatCounterCore::init() {
  addParameter(PRM_RESET, "Reset", TYP_BOOL, 0.0, 1.0, 0.0);
  addParameter(PRM_TOLERANCE, "Tolerance", TYP_PERCENT, 0.0, 100.0, 75.0);
  addParameter(PRM_PERIOD, "Period", TYP_SECONDS, 5.0, 20.0, 10.0);
  addParameter(PRM_AUTOFILTER, "Autofilter On", TYP_BOOL, 0.0, 1.0, 0.0);
  addParameter(PRM_AUTOFILTER_FREQ, "Autofilter Freq.", TYP_HZ, 60.0, 400.0, 400.0);
  addParameter(PRM_LINK, "Link to Host", TYP_BOOL, 0.0, 1.0, 0.0);
  addParameter(PRM_LINK_BPM, "Link Tolerance", TYP_BPM, 4.0, 12.0, 8.0);
  addParameter(PRM_SAMPLE_RATE, "Sample Rate", TYP_HZ, 32000, 96000, 44100, true);
  addParameter(PRM_HOST_BPM, "Host BPM", TYP_BPM, MIN_BPM, MAX_BPM, 120.0, true);
  addParameter(PRM_ACCUM_BPM, "Accum BPM", TYP_BPM, MIN_BPM, MAX_BPM, 0.0, true);
  addParameter(PRM_CURRENT_BPM, "Current BPM", TYP_BPM, MIN_BPM, MAX_BPM, 0.0, true);
  addParameter(PRM_BEAT_TRIGGER, "Beat Trigger", TYP_BOOL, 0.0, 1.0, 0.0);
  
  editor = 0;
  reset();

}

BeatCounterCore::~BeatCounterCore() {
}

const inline float BeatCounterCore::fabs(float f) const {
  if(f >= 0.0) {
    return f;
  }
  else {
    return -f;
  }
}

void BeatCounterCore::reset() {
  m_num_samples_processed = 0;
  m_high_point = 0.0;
  m_bar_high_point = 0.0;
  m_bar_high_avg = 0.0;
  m_bar_samp_avg = 0.0;
  m_beat_state = false;
  m_downsampled_index = 0;
  m_last_avg = 0;
  m_beat_samples = 0;
  m_autofilter_out1 = 0.0;
}

*/