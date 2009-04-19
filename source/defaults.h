/*
 *  BeatCounter - defaults.h
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __defaults_H
#define __defaults_H

#define DEF_PRODUCT "BeatCounter"
#define MAJ_VERSION 1
#define MIN_VERSION 5
#define REL_BRANCH 'r'
#define VERSION ((MAJ_VERSION * 1000) + (MIN_VERSION * 10))

enum {
  PRM_RESET,
  PRM_TOLERANCE,
  PRM_PERIOD,
  PRM_AUTOFILTER,
  PRM_AUTOFILTER_FREQ,
  PRM_LINK,
  PRM_LINK_BPM,
  PRM_SAMPLE_RATE,
  PRM_HOST_BPM,
  PRM_CURRENT_BPM,
  PRM_ACCUM_BPM,
  PRM_BEAT_TRIGGER,
  NUM_PARAMS
};

enum {
#ifdef MAC
  REZ_BACKGROUND = 10001,
#else ifdef WINDOWS
  REZ_BACKGROUND = 1,
#endif
  REZ_BEAT_BUTTON,
  REZ_SPLASHSCREEN,
  REZ_RESET_BUTTON,
  REZ_FILTER_BUTTON,
  REZ_LINK_BUTTON
};

// Additional GUI parameters defined here so they don't get in the way of
// the actual parameters
enum {
  TAG_BEAT_BUTTON = NUM_PARAMS,
  TAG_SPLASH
};

#define DEF_ANIMATION_FRAMES 5
#define DEF_ANIMATION_TICKS 8

#define DEF_DOWNSAMPLE 1000 // Downsampling rate
#define DEF_TEMPO 120

#define MIN_AMPLITUDE 0.1 // Used to filter noise
#define MIN_BPM 60
#define MAX_BPM 180 // Helps to improve accuracy

// PluginCore features
#define USE_PC_EVENTS 0

#ifdef USE_PC_AU
#define BeatCounter_COMP_SUBTYPE 'BtCt'
#define BeatCounter_COMP_MANF 'Tera'
#define kBeatCounterVersion 0x00010000
#endif

#ifdef USE_PC_VST
#define NUM_INPUTS 2
#define NUM_OUTPUTS 2
#define UNIQUE_ID 'BtCt'
#endif

#endif