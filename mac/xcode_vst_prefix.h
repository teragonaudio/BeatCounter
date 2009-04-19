#define MAC 1
#define MACX 1
#define QUARTZ 1
#define TARGET_API_MAC_CARBON 1
#define USENAVSERVICES 1

#define __CF_USE_FRAMEWORK_INCLUDES__

#if __MWERKS__
#define __NOEXTENSIONS__
#endif

#define MAC_OS_X_VERSION_MIN_REQUIRED   1020
#define MAC_OS_X_VERSION_MAX_ALLOWED	1030

#include <Carbon/Carbon.h>
#include <AvailabilityMacros.h>

// Needed to get the VSTGUI 3.0 to work with the VST 2.4 SDK
#if __ppc__
#define VST_FORCE_DEPRECATED 0
#else
#define VST_FORCE_DEPRECATED 1
#endif