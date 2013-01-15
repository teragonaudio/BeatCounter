/*
 *  RefreshTextLabelsTimer.cpp
 *  BeatCounter
 *
 *  Created by Nik Reiman on 2010-04-08.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#include "RefreshTextLabelsTimer.h"

namespace teragon {
  RefreshTextLabelsTimer::RefreshTextLabelsTimer(RefreshTextLabelsTimerResponder* inResponder) :
  Timer() {
    this->responder = inResponder;
  }
  
  RefreshTextLabelsTimer::~RefreshTextLabelsTimer() {
  }
  
  void RefreshTextLabelsTimer::timerCallback() {
    this->responder->onTextLabelsRefresh();
  }
}