/*
 *  RefreshTextLabelsTimerResponder.h
 *  BeatCounter
 *
 *  Created by Nik Reiman on 2010-04-08.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __RefreshTextLabelsTimerResponder_h__
#define __RefreshTextLabelsTimerResponder_h__

namespace teragon {
  class RefreshTextLabelsTimerResponder {
  public:
    RefreshTextLabelsTimerResponder() {}
    virtual ~RefreshTextLabelsTimerResponder() {}
    
    virtual void onTextLabelsRefresh() = 0;
  };
}

#endif