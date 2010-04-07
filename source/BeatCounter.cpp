/*
 *  BeatCounter - BeatCounter.cpp
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __BeatCounterCore_H
#include "BeatCounter.h"
#endif

/*
#ifndef __audioeffectx__
#include "public.sdk/source/vst2.x/audioeffectx.h"
#endif
*/

#include <math.h>

AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new teragon::BeatCounter();
}

namespace teragon {
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
  }

  void BeatCounter::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
  }

  void BeatCounter::releaseResources() {
  }

  void BeatCounter::reset() {
  }

  AudioProcessorEditor* BeatCounter::createEditor() {
    return 0;
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
  m_min_bpm = MIN_BPM;
  m_max_bpm = MAX_BPM;
  m_dupe_interval = (long)(44100 * (float)(60.0f / (float)m_max_bpm));  
  m_downsample_rate = DEF_DOWNSAMPLE;
  m_skip_count = m_downsample_rate;
  m_downsampled = new float[(int)((44100 * 20) / m_downsample_rate)];
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

void BeatCounterCore::process(float **inputs, float **outputs, long frames) {
  float *in_left = inputs[0];
  float *in_right = inputs[1];
  float *out_left = outputs[0];
  float *out_right = outputs[1];
  
  while(--frames >= 0) {
    float mono;
    
    if(PARAM(PRM_AUTOFILTER)) {
      // Lowpass filter
      m_autofilter_out1 = m_autofilter_out1 + (float)(1.0 / (PARAM(PRM_SAMPLE_RATE) *
                                                             (1.0 / (2.0 * M_PI *
                                                                     PARAM(PRM_AUTOFILTER_FREQ))))) * 
      (*in_left - m_autofilter_out1);
      mono = fabs(m_autofilter_out1);
    }
    else {
      mono = fabs(*in_left);
    }
    
    // Find highest peak in downsampled area ("bar")
    if(mono > m_bar_high_point) {
      m_bar_high_point = mono;
      
      // Find highest averaging value for testing period
      if(mono > m_high_point) {
        m_high_point = mono;
      }  
    }
    
    // Process one "bar"
    if(--m_skip_count <= 0) {
      // Calculate average point
      m_bar_samp_avg /= m_downsample_rate;
      
      // Beat amplitude/frequency has been detected
      if(m_bar_samp_avg >= (m_bar_high_avg * PARAM(PRM_TOLERANCE) / 100.0) &&
         m_bar_high_point >= (m_high_point * PARAM(PRM_TOLERANCE) / 100.0) &&
         m_bar_high_point > MIN_AMPLITUDE) {
        
        // First bar in a beat?
        if(!m_beat_state && m_beat_samples > m_dupe_interval) {
          m_beat_state = true;
          float bpm = (float)((PARAM(PRM_SAMPLE_RATE) * 60.0f) /
                              ((m_last_avg + m_beat_samples) / 2));
          
          // Check for half-beat patterns
          float hbpm = bpm * 2.0;
          if(hbpm > m_min_bpm && hbpm < m_max_bpm) {
#ifdef DEBUG
            fprintf(stderr, "Half beat detected\n");
#endif
            bpm = hbpm;
          }
          
          // See if we're inside the threshhold
          if(bpm > m_min_bpm && bpm < m_max_bpm) {
            setParameter(PRM_CURRENT_BPM, bpm, true);
            // Set the running bpm in the editor window & turn on light
#if AU
            setParameter(PRM_BEAT_TRIGGER, 1.0, true);
#elif VST
            if(editor) {
              ((BeatCounterEditor*)editor)->setBeatLight();
              ((BeatCounterEditor*)editor)->setBPMDisplay(bpm, -1);
            }
#endif
          
            m_last_avg += m_beat_samples;
            m_last_avg /= 2;
            m_beat_samples = 0;
            m_bpm_history.push_back(bpm);
            
            // Do total BPM and Reset?
            if(m_num_samples_processed > (PARAM(PRM_PERIOD) * PARAM(PRM_SAMPLE_RATE))) {
              // Take advantage of this trigger point to do a tempo check
              if(PARAM(PRM_LINK)) {
                m_min_bpm = PARAM(PRM_HOST_BPM) - PARAM(PRM_LINK_BPM);
                m_max_bpm = PARAM(PRM_HOST_BPM) + PARAM(PRM_LINK_BPM);
                m_dupe_interval = (long)(PARAM(PRM_SAMPLE_RATE) * (float)(60.0f / (float)m_max_bpm));
              }
              
              float total = 0.0f;
              unsigned int i;
              for(i = 0; i < m_bpm_history.size(); ++i) {
                total += m_bpm_history.at(i);
              }
#if VST
              ((BeatCounterEditor*)editor)->setBPMDisplay(-1, (float)(total / i));
#endif
              setParameter(PRM_ACCUM_BPM, (float)(total / i), true);
              m_bpm_history.clear();
              m_num_samples_processed = 0;
            }
          }
          else {
#ifdef DEBUG
            fprintf(stderr, "BPM of %f is outside of threshhold!\n", bpm);
#endif
            // outside of bpm threshhold
#if AU
            setParameter(PRM_CURRENT_BPM, bpm * -1.0, true);
#elif VST
            if(editor) {
              ((BeatCounterEditor*)editor)->setBeatLight();
              ((BeatCounterEditor*)editor)->setBPMDisplay(bpm * -1.0, -1);
            }
#endif     
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
      m_bar_samp_avg += mono;
    }
    
#ifdef DEBUG
    (*in_left++);
    (*in_right++);
    (*out_left++) = mono;
    (*out_right++) = mono;
#else
    // Pass audio through; we don't care
    (*out_left++) = (*in_left++);
    (*out_right++) = (*in_right++);
#endif
    
    ++m_num_samples_processed;
    ++m_beat_samples;
  }  
}

// Used to push the editor from the host to the core
void BeatCounterCore::setEditor(BeatCounterEditor *e) {
  editor = e;
}
*/