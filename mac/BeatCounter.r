/*
 *  BeatCounter - BeatCounter.r
 *  Created by Nik Reiman on 22.01.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#include <AudioUnit/AudioUnit.r>

#ifndef __defaults_H
#include "defaults.h"
#endif

// Note that resource IDs must be spaced 2 apart for the 'STR ' name and description
#define kAudioUnitResID_BeatCounter 1000
#define kAudioUnitResID_BeatCounterView 2000

#define BeatCounter_COMP_SUBTYPE 'BtCt'
#define BeatCounter_COMP_MANF 'Tera'
#define kBeatCounterVersion 0x00010000

//////////////////////////////////////////////////////////////////////////////

#define RES_ID kAudioUnitResID_BeatCounter
#define COMP_TYPE kAudioUnitType_Effect
#define COMP_SUBTYPE BeatCounter_COMP_SUBTYPE
#define COMP_MANUF BeatCounter_COMP_MANF	

#define VERSION kBeatCounterVersion
#define NAME "Teragon Audio: BeatCounter"
#define DESCRIPTION "BeatCounter AU"
#define ENTRY_POINT "BeatCounterEntry"

#include "AUResources.r"

//////////////////////////////////////////////////////////////////////////////

#define RES_ID kAudioUnitResID_BeatCounterView
#define COMP_TYPE kAudioUnitCarbonViewComponentType
#define COMP_SUBTYPE BeatCounter_COMP_SUBTYPE
#define COMP_MANUF BeatCounter_COMP_MANF	

#define VERSION kBeatCounterVersion
#define NAME "Teragon Audio: BeatCounter"
#define DESCRIPTION "BeatCounter VSTGUI AUView"
#define ENTRY_POINT "BeatCounterViewEntry"

#include "AUResources.r"