/*
 *  BeatCounter - BeatCounterVST.cpp
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __BeatCounterVST_H
#include "BeatCounterVST.h"
#endif

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new BeatCounter(audioMaster);
}

BeatCounter::BeatCounter(audioMasterCallback audioMaster)
  : AudioEffectX(audioMaster, 0, NUM_PARAMS) {
  setNumInputs(NUM_INPUTS);
  setNumOutputs(NUM_OUTPUTS);
  setUniqueID(UNIQUE_ID);
  
  strcpy(mProgramName, "Default"); // default program name

  editor = new BeatCounterEditor(this);
  core = new BeatCounterCore(NUM_PARAMS, VERSION, DEF_PRODUCT);
  core->setEditor((BeatCounterEditor*)editor);
  core->setParameter(PRM_SAMPLE_RATE, getSampleRate(), true);
}

BeatCounter::~BeatCounter() {
}

VstInt32 BeatCounter::canDo(char *text) {
  // TODO: Fill in according to your plugin's capabilities
  
  return 0;
}

bool BeatCounter::getEffectName(char* name) {
  strcpy(name, "BeatCounter");
  return true;
}

float BeatCounter::getParameter(VstInt32 index) {
  return core->getParameter(REQ_VALUE, index, NULL);
}

void BeatCounter::getParameterDisplay(VstInt32 index, char *text) {
  core->getParameter(REQ_DISPLAY, index, text);
}

void BeatCounter::getParameterLabel(VstInt32 index, char *label) {
  core->getParameter(REQ_LABEL, index, label);
}

void BeatCounter::getParameterName(VstInt32 index, char *text) {
  core->getParameter(REQ_NAME, index, text);
}

VstPlugCategory BeatCounter::getPlugCategory() {
  return kPlugCategEffect;
}

bool BeatCounter::getProductString(char* text) {
  strcpy(text, "BeatCounter");
  return true;
}

void BeatCounter::getProgramName(char *name) {
  strcpy(name, mProgramName);
}

bool BeatCounter::getVendorString(char* text) {
  strcpy(text, "Teragon Audio");
  return true;
}

VstInt32 BeatCounter::getVendorVersion() {
  return 1000;
}

void BeatCounter::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
  VstTimeInfo *vt = getTimeInfo(kVstClockValid);
  core->setParameter(PRM_HOST_BPM, vt->tempo, true);
  core->process(inputs, outputs, sampleFrames);
}

void BeatCounter::setParameter(VstInt32 index, float value) {
  core->setParameter(index, value);
}

void BeatCounter::setProgramName(char *name) {
  strcpy(mProgramName, name);
}
