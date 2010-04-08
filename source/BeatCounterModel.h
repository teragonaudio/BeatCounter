/*
 *  BeatCounterModel.h
 *  BeatCounter
 *
 *  Created by Nik Reiman on 2010-04-08.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __BeatCounterModel_h__
#define __BeatCounterModel_h__

namespace teragon {
  class BeatCounterModel {
  public:
    BeatCounterModel() {};
    virtual ~BeatCounterModel() {};
    
    virtual const float getCurrentBpm() const = 0;
    virtual const float getRunningBpm() const = 0;
    
    virtual void setHostLink(bool isEnabled) = 0;
    virtual void setAutofilter(bool isEnabled) = 0;
  };
}

#endif
