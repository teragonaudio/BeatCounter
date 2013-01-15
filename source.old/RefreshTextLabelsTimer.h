/*
 *  RefreshTextLabelsTimer.h
 *  BeatCounter
 *
 *  Created by Nik Reiman on 2010-04-08.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __RefreshTextLabelsTimer_h__
#define __RefreshTextLabelsTimer_h__

#include "juce.h"

#ifndef __RefreshTextLabelsTimerResponder_h__
#include "RefreshTextLabelsTimerResponder.h"
#endif

namespace teragon {
  class RefreshTextLabelsTimer : public Timer {
  public:
    RefreshTextLabelsTimer(RefreshTextLabelsTimerResponder* inResponder);
    ~RefreshTextLabelsTimer();
    
    void timerCallback();
    
  private:
    RefreshTextLabelsTimerResponder *responder;
  };
}

#endif
