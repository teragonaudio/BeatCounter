/*
 *  BeatCounter - BeatCounterAU.h
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __BeatCounterAU_H
#define __BeatCounterAU_H

#ifndef __BeatCounterCore_H
#include "BeatCounterCore.h"
#endif

#ifndef __BeatCounterEditor_H
#include "BeatCounterEditor.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#include "AUCarbonViewBase.h"
#include "AUCarbonViewControl.h"
#include "AUEffectBase.h"

#if AU_DEBUG_DISPATCHER
#include "AUDebugDispatcher.h"
#endif

class BeatCounter : public AUEffectBase {
  public:
    BeatCounter(AudioUnit component);
  #if AU_DEBUG_DISPATCHER
    virtual ~BeatCounter() { delete mDebugDispatcher; }
  #endif
    
    virtual int GetNumCustomUIComponents();
    virtual	ComponentResult GetParameterValueStrings(AudioUnitScope inScope,
                                                     AudioUnitParameterID inParameterID,
                                                     CFArrayRef *outStrings);
    virtual ComponentResult GetParameter(AudioUnitParameterID inID,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         Float32& outValue);
    virtual	ComponentResult GetParameterInfo(AudioUnitScope inScope,
                                             AudioUnitParameterID	inParameterID,
                                             AudioUnitParameterInfo	&outParameterInfo);
    virtual void GetUIComponentDescs(ComponentDescription* inDescArray);
    virtual OSStatus ProcessBufferLists(AudioUnitRenderActionFlags &ioActionFlags,
                                        const AudioBufferList &inBuffer,
                                        AudioBufferList &outBuffer,
                                        UInt32 inFramesToProcess);
    virtual ComponentResult SetParameter(AudioUnitParameterID inID,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         Float32 inValue,
                                         UInt32 inBufferOffsetInFrames);
    virtual	bool SupportsTail();
    virtual ComponentResult	Version();
  
  protected:
  private:
    BeatCounterCore *core;
    PluginGUIEditor *editor;
};

#endif