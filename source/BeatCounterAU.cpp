/*
 *  BeatCounter - BeatCounterAU.cpp
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */


#ifndef __BeatCounterAU_H
#include "BeatCounterAU.h"
#endif

COMPONENT_ENTRY(BeatCounter);

BeatCounter::BeatCounter(AudioUnit component) : AUEffectBase(component) {
	CreateElements();
	Globals()->UseIndexedParameters(NUM_PARAMS);
  
  core = new BeatCounterCore(NUM_PARAMS, VERSION, DEF_PRODUCT);
  core->setEditor((BeatCounterEditor*)editor);
  
#if AU_DEBUG_DISPATCHER
	mDebugDispatcher = new AUDebugDispatcher(this);
#endif
}

int BeatCounter::GetNumCustomUIComponents() {
  return 1;
}

ComponentResult BeatCounter::GetParameter(AudioUnitParameterID inID,
                                            AudioUnitScope inScope,
                                            AudioUnitElement inElement,
                                            Float32& outValue) {
  outValue = core->getParameter(REQ_VALUE, inID, NULL);
  return noErr;
}

ComponentResult	BeatCounter::GetParameterInfo(AudioUnitScope inScope,
                                                AudioUnitParameterID inParameterID,
                                                AudioUnitParameterInfo &outParameterInfo) {
	ComponentResult result = noErr;
  
	outParameterInfo.flags = kAudioUnitParameterFlag_IsWritable
    |	kAudioUnitParameterFlag_IsReadable;
  
  if(inScope == kAudioUnitScope_Global) {
    char *c_name = new char[24];
    core->getParameter(REQ_NAME, inParameterID, c_name);
    CFStringRef name = CFStringCreateWithCString(kCFAllocatorDefault, c_name, 0);
    delete [] c_name;
    
    AUBase::FillInParameterName(outParameterInfo, name, false);
    outParameterInfo.unit = (AudioUnitParameterUnit)core->getParameter(REQ_LABEL, inParameterID, NULL);
    outParameterInfo.minValue = core->getParameter(REQ_VALUE_MIN, inParameterID, NULL);
    outParameterInfo.maxValue = core->getParameter(REQ_VALUE_MAX, inParameterID, NULL);
    outParameterInfo.defaultValue = core->getParameter(REQ_VALUE_DEF, inParameterID, NULL);
	}
  else {
    result = kAudioUnitErr_InvalidParameter;
  }
  
	return result;
}

ComponentResult	BeatCounter::GetParameterValueStrings(AudioUnitScope inScope,
                                                        AudioUnitParameterID inParameterID,
                                                        CFArrayRef *outStrings) {
  return kAudioUnitErr_InvalidProperty;
}

void BeatCounter::GetUIComponentDescs(ComponentDescription* inDescArray) {
  inDescArray[0].componentType = kAudioUnitCarbonViewComponentType;
  inDescArray[0].componentSubType = BeatCounter_COMP_SUBTYPE;
  inDescArray[0].componentManufacturer = BeatCounter_COMP_MANF;
  inDescArray[0].componentFlags = 0;
  inDescArray[0].componentFlagsMask = 0;
}

OSStatus BeatCounter::ProcessBufferLists(AudioUnitRenderActionFlags &ioActionFlags,
                                         const AudioBufferList &inBuffer,
                                         AudioBufferList &outBuffer,
                                         UInt32 inFramesToProcess) {
  // call the kernels to handle either interleaved or deinterleaved
	if(inBuffer.mNumberBuffers == 1) {
    // process each interleaved channel individually
    float **inputs = new float*[2];
    inputs[0] = (float*)inBuffer.mBuffers[0].mData;
    inputs[1] = (float*)inBuffer.mBuffers[0].mData + 1;
    
    float **outputs = new float*[2];
    outputs[0] = (float*)outBuffer.mBuffers[0].mData;
    outputs[1] = (float*)outBuffer.mBuffers[0].mData + 1;
    
    core->process(inputs, outputs, inFramesToProcess);
	}
  else {
    float **inputs = new float*[2 * sizeof(float*)];
    inputs[0] = (float*)inBuffer.mBuffers[0].mData;
    inputs[1] = (float*)inBuffer.mBuffers[1].mData;
    
    float **outputs = new float*[2 * sizeof(float*)];
    outputs[0] = (float*)outBuffer.mBuffers[0].mData;
    outputs[1] = (float*)outBuffer.mBuffers[1].mData;
    
    core->process(inputs, outputs, inFramesToProcess);
  }
  
  return noErr;
}

ComponentResult BeatCounter::SetParameter(AudioUnitParameterID inID,
                                          AudioUnitScope inScope,
                                          AudioUnitElement inElement,
                                          Float32 inValue,
                                          UInt32 inBufferOffsetInFrames) {
  core->setParameter(inID, inValue);
  return noErr;
}

bool BeatCounter::SupportsTail() {
  return false;
}

ComponentResult BeatCounter::Version() {
  return kBeatCounterVersion;
}