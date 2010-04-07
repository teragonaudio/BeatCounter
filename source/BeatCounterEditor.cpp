/*
 *  BeatCounter - BeatCounterEditor.cpp
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __BeatCounterEditor_h__
#include "BeatCounterEditor.h"
#endif

namespace teragon {
  BeatCounterEditor::BeatCounterEditor(AudioProcessor* audioProcessor) : AudioProcessorEditor(audioProcessor) {
  }
  
  BeatCounterEditor::~BeatCounterEditor() {
  }
}

/*
// VSTGUI implementation //////////////////////////////////////////////////////////////

#if PLUGGUI
BeatCounterEditor::BeatCounterEditor(void *effect) : AEffGUIEditor(effect) {
#else
BeatCounterEditor::BeatCounterEditor(AudioEffect *effect) : AEffGUIEditor(effect) {
#endif
  mOpened = false;
  m_current_bpm = 0;
  m_accum_bpm = 0;
  m_beat_ticks = 0;
  m_animate_up = false;
  m_animate_down = false;
  m_animate_count = 0;
    
  mBackground = new CBitmap(REZ_BACKGROUND);
  rect.left = 0;
  rect.top = 0;
  rect.right = (short)mBackground->getWidth();
  rect.bottom = (short)mBackground->getHeight();
}

BeatCounterEditor::~BeatCounterEditor() {
  if(mBackground) {
    mBackground->forget();
  }
  mBackground = 0;
}

void BeatCounterEditor::close() {  
  mOpened = false;
  delete frame;
  frame = 0;
}

void BeatCounterEditor::idle() {
  AEffGUIEditor::idle();
 
#if USE_PC_AU
  Float32 value = 0.0;
  AudioUnitGetParameter((ComponentInstanceRecord*)effect, PRM_BEAT_TRIGGER, kAudioUnitScope_Global, 0, &value);
  if(value) {
    setBeatLight();
    AudioUnitSetParameter((ComponentInstanceRecord*)effect, PRM_BEAT_TRIGGER, kAudioUnitScope_Global, 0, 0.0, 0);
  }
#endif
  
  if(mOpened) {
    if(m_animate_up) {
      long ticks = getTicks();
      if(ticks > m_beat_ticks + DEF_ANIMATION_TICKS) {
        m_beat_ticks = ticks;
        m_beat_button->setValue((float)(++m_animate_count) / (float)DEF_ANIMATION_FRAMES);
        if(++m_animate_count > DEF_ANIMATION_FRAMES) {
          m_animate_count = 0;
          m_animate_up = false;
          m_animate_down = true;
        }
      }
    }
    else if(m_animate_down) {
      long ticks = getTicks();
      if(ticks > m_beat_ticks + DEF_ANIMATION_TICKS) {
        m_beat_ticks = ticks;
        m_beat_button->setValue((float)(1.0 - (float)(++m_animate_count) / (float)DEF_ANIMATION_FRAMES));
        if(m_animate_count > DEF_ANIMATION_FRAMES) {
          m_animate_count = 0;
          m_animate_down = false;
          m_beat_button->setValue(0.0);
        }
      }
    }
  }
  
#if USE_PC_AU
  // We have to pull data from AU, it doesn't get pushed like from VST
  // TODO: Maybe change the VST port to match this someday...
  Float32 cbpm, abpm;
  AudioUnitGetParameter((ComponentInstanceRecord*)effect, PRM_CURRENT_BPM, kAudioUnitScope_Global, 0, &cbpm);
  AudioUnitGetParameter((ComponentInstanceRecord*)effect, PRM_ACCUM_BPM, kAudioUnitScope_Global, 0, &abpm);
  setBPMDisplay(cbpm, abpm);
#endif
}

bool BeatCounterEditor::open(void *ptr) {
  AEffGUIEditor::open(ptr);
  
  CRect size(0, 0, mBackground->getWidth(), mBackground->getHeight());
  CPoint point(0, 0);
  frame = new CFrame(size, ptr, this);
  frame->setBackground(mBackground);
  
  // Current BPM display
  size(17,25, 102,46);
  CColor almost_trans = {255, 255, 255, 130};
  m_current_bpm = new CParamDisplay(size, 0, kCenterText);
  m_current_bpm->setFont(kNormalFontVeryBig);
  m_current_bpm->setFontColor(kBlackCColor);
  m_current_bpm->setBackColor(almost_trans);
  m_current_bpm->setFrameColor(kBlackCColor);
  m_current_bpm->setValue(000);
  frame->addView(m_current_bpm);
  
  // Cumulative BPM display
  size(17,62, 102,83);
  m_accum_bpm = new CParamDisplay(size, 0, kCenterText);
  m_accum_bpm->setFont(kNormalFontVeryBig);
  m_accum_bpm->setFontColor(kBlackCColor);
  m_accum_bpm->setBackColor(almost_trans);
  m_accum_bpm->setFrameColor(kBlackCColor);
  m_accum_bpm->setValue(000);
  frame->addView(m_accum_bpm);
  
  CBitmap *btn;
  // Blinking beat light
  size(177,16, 202,41);
  btn = new CBitmap(REZ_BEAT_BUTTON);
  m_beat_button = new CMovieBitmap(size, this, TAG_BEAT_BUTTON, DEF_ANIMATION_FRAMES,
                                   btn->getHeight() / DEF_ANIMATION_FRAMES, btn, point);
  frame->addView(m_beat_button);
  m_beat_button->setValue(0.0);
  btn->forget();
  
  // Splashscreen
  size(185,72, 200,87);
  btn = new CBitmap(REZ_SPLASHSCREEN);
  CRect display_area(0, 0, btn->getWidth(), btn->getHeight());
  display_area.offset(0, 0);
  m_splashscreen = new CSplashScreen(size, this, TAG_SPLASH, btn, display_area, point);
  frame->addView(m_splashscreen);
  btn->forget();
  
  // Autofilter button
  size(130,13, 168,35);
  btn = new CBitmap(REZ_FILTER_BUTTON);
  m_filter_button = new COnOffButton(size, this, PRM_AUTOFILTER, btn, COnOffButton::kPreListenerUpdate);
  frame->addView(m_filter_button);
  btn->forget();
  
  // Reset button
  size(130,41, 168,63);
  btn = new CBitmap(REZ_RESET_BUTTON);
  m_reset_button = new CKickButton(size, this, PRM_RESET, btn->getHeight() / 2, btn, point);
  frame->addView(m_reset_button);  
  btn->forget();
  
  // BPM Link button
  size(130,69, 168,91);
  btn = new CBitmap(REZ_LINK_BUTTON);
  m_link_button = new COnOffButton(size, this, PRM_LINK, btn, COnOffButton::kPreListenerUpdate);
  frame->addView(m_link_button);
  btn->forget();
  
  mOpened = true;
  return true;
}

void BeatCounterEditor::setBeatLight() {
  m_animate_up = true;
  m_animate_down = false;
}

void BeatCounterEditor::setBPMDisplay(float c_bpm, float a_bpm) {
  if(mOpened) {
    if(m_current_bpm && c_bpm >= 0) {
      m_current_bpm->setFontColor(kBlackCColor);
      m_current_bpm->setValue((float)c_bpm);
    }
    else if(c_bpm < -1.0) {
      m_current_bpm->setFontColor(kRedCColor);
      m_current_bpm->setValue((float)c_bpm * -1.0);
    }
    
    if(m_accum_bpm && a_bpm >= 0) {
      m_accum_bpm->setValue(a_bpm);
    }
  }
}

void BeatCounterEditor::valueChanged(CDrawContext* context, CControl* control) {
  if(control->getTag() == PRM_RESET) {
    setBPMDisplay(0.0, 0.0);
  }
#if USE_PC_AU
  AudioUnitSetParameter((ComponentInstanceRecord*)effect, control->getTag(), kAudioUnitScope_Global, 0, control->getValue(), 0);
#elif USE_PC_VST
  ((AudioEffect*)effect)->setParameter(control->getTag(), control->getValue());
#endif
}

// AU VSTGUI hooks ///////////////////////////////////////////////////////////////////////

#ifdef USE_PC_AU
COMPONENT_ENTRY(BeatCounterView);

BeatCounterView::BeatCounterView(AudioUnitCarbonView auv) 
: AUCarbonViewBase(auv), editor(0), xOffset(0), yOffset(0) {
}

BeatCounterView::~BeatCounterView() {
  if(editor) {
    editor->close();
  }
}

void BeatCounterView::RespondToEventTimer(EventLoopTimerRef inTimer) {
  if(editor) {
    editor->idle();
  }
}

OSStatus BeatCounterView::CreateUI(Float32 xoffset, Float32 yoffset) {
  AudioUnit unit = GetEditAudioUnit();
  if(unit) {
    editor = new BeatCounterEditor(unit);
    WindowRef window = GetCarbonWindow();
    editor->open(window);
    HIViewMoveBy((HIViewRef)editor->getFrame()->getPlatformControl(), xoffset, yoffset);
    EmbedControl((HIViewRef)editor->getFrame()->getPlatformControl());
    CRect fsize = editor->getFrame()->getViewSize(fsize);
    SizeControl(mCarbonPane, fsize.width(), fsize.height());
    CreateEventLoopTimer(kEventDurationSecond, kEventDurationSecond / 24);
    HIViewSetVisible((HIViewRef)editor->getFrame()->getPlatformControl(), true);
    HIViewSetNeedsDisplay((HIViewRef)editor->getFrame()->getPlatformControl(), true);
  }
  return noErr;
}
#endif

*/