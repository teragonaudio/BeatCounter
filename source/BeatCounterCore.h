/*
 *  BeatCounter - BeatCounterCore.h
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */


#ifndef __BeatCounterCore_H
#define __BeatCounterCore_H

#ifndef __BeatCounterEditor_H
#include "BeatCounterEditor.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#include <vector>

class BeatCounterCore {
  /*
  public:
    BeatCounterCore(int num_params, int version, char *name);
    ~BeatCounterCore();
    
    const float fabs(float f) const;
    void process(float **inputs, float **outputs, long frames);
    void setEditor(BeatCounterEditor *e);
    void reset();
    
  protected:
  private:    
    void init();
    
    BeatCounterEditor *editor;
    std::vector<float> m_bpm_history;
    
    bool m_beat_state;
    
    float *m_downsampled;
    float m_high_point;
    float m_bar_high_point;
    float m_bar_high_avg;
    float m_bar_samp_avg;
    float m_total_seconds_running;
    float m_last_avg;
    float m_min_bpm;
    float m_max_bpm;
    
    float m_autofilter_const;
    float m_autofilter_freq;
    float m_autofilter_out1;
    
    int m_downsampled_index;
    int m_beat_marks_index;
    int m_avg_bpm_index;
    
    unsigned long m_skip_count;
    unsigned long m_downsample_rate;
    unsigned long m_last_beat_counted;
    unsigned long m_num_samples_processed;
    unsigned long m_dupe_interval;
    unsigned long m_beat_samples;
    */
};

#endif
