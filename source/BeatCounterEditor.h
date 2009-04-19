/*
 *  BeatCounter - BeatCounterEditor.h
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __BeatCounterEditor_H
#define __BeatCounterEditor_H

#ifdef USE_PC_AU
#include <Carbon/Carbon.h>
#include "AUCarbonViewBase.h"
#include "AUEffectBase.h"
#endif

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

#ifndef __vstgui__
#include "vstgui.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

class BeatCounterEditor : public AEffGUIEditor, public CControlListener {
  public:
#if PLUGGUI
    BeatCounterEditor(void *effect);
#else
    BeatCounterEditor(AudioEffect *effect);
#endif
    ~BeatCounterEditor();
    
    virtual void close();
    virtual void idle();
    virtual bool open(void *ptr);
    void setBeatLight();
    void setBPMDisplay(float c_bpm, float a_bpm);
    virtual void valueChanged(CDrawContext* context, CControl* control);
    
  protected:
      
  private:
    CBitmap *mBackground;
    CParamDisplay *m_current_bpm;
    CParamDisplay *m_accum_bpm;
    CKickButton *m_reset_button;
    COnOffButton *m_filter_button;
    COnOffButton *m_link_button;
    CSplashScreen *m_splashscreen;
    CMovieBitmap *m_beat_button;
        
    bool mOpened;
    bool m_animate_up;
    bool m_animate_down;
    int m_animate_count;
    int m_beat_ticks;
};

#ifdef USE_PC_AU
class BeatCounterView : public AUCarbonViewBase  {
  public:
    BeatCounterView(AudioUnitCarbonView auv);  
    virtual ~BeatCounterView();
    
    void RespondToEventTimer(EventLoopTimerRef inTimer);
    virtual OSStatus CreateUI(Float32 xoffset, Float32 yoffset);  
    
    Float32 xOffset;
    Float32 yOffset;
  protected:
    BeatCounterEditor* editor;
  
  private:
};
#endif

#endif