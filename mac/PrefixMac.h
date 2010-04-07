#define MAC 1
#define MACX 1
#define PLUGGUI 1
#define QUARTZ 1
#define TARGET_API_MAC_CARBON 1
#define USENAVSERVICES 1
#define MAC_OS_X_VERSION_MIN_REQUIRED   1020
#define MAC_OS_X_VERSION_MAX_ALLOWED	1030

#if __ppc__
#define VST_FORCE_DEPRECATED 0
#else
#define VST_FORCE_DEPRECATED 1
#endif

#if __MWERKS__
#define __NOEXTENSIONS__
#endif

#define PluginGUIEditor AEffGUIEditor

#include <Carbon/Carbon.h>
#include <AudioUnit/AudioUnit.h>
#include <AvailabilityMacros.h>
#include "vstgui.h"

#include "defaults.h"