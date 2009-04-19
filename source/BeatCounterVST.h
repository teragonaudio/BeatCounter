/*
 *  BeatCounter - BeatCounterVST.h
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __BeatCounter_H
#define __BeatCounter_H

#ifndef __BeatCounterCore_H
#include "BeatCounterCore.h"
#endif

#ifndef __BeatCounterEditor_H
#include "BeatCounterEditor.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#ifndef __audioeffect__
#include "audioeffectx.h"
#endif

class BeatCounter : public AudioEffectX {
  public:
    BeatCounter(audioMasterCallback audioMaster);
    ~BeatCounter();

    virtual VstInt32 canDo(char *text);
    virtual bool getEffectName(char* name);

    virtual float getParameter(VstInt32 index);
    virtual void getParameterDisplay(VstInt32 index, char *text);
    virtual void getParameterLabel(VstInt32 index, char *label);
    virtual void getParameterName(VstInt32 index, char *text);

    virtual VstPlugCategory getPlugCategory();
    virtual bool getProductString(char* text);
    virtual void getProgramName(char *name);
    virtual bool getVendorString(char* text);
    virtual VstInt32 getVendorVersion();
  
    virtual void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);

    virtual void setParameter(VstInt32 index, float value);
    virtual void setProgramName(char *name);

  protected:
    char mProgramName[32];

  private:
    BeatCounterCore *core;
};

#endif
