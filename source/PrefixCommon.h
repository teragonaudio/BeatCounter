#define PLUGIN_NAME "BeatCounter"
#define PLUGIN_NAME_FOURCC 'BtCt'
#define PLUGIN_MANUFACTURER "Teragon Audio"
#define PLUGIN_MANUFACTURER_FOURCC 'Tera'

#define VERSION_MAJOR 2
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define VERSION_STRING "2.0.0"
#define VERSION_NUMBER ((VERSION_MAJOR * 10000) + (VERSION_MINOR * 100) + VERSION_PATCH)

enum Parameters {
  kParamReset,
  kParamTolerance,
  kParamPeriod,
  kParamAutofilterEnabled,
  kParamAutofilterFrequency,
  kParamLinkToHostTempo,
  
  kNumParams
};

enum {
#if MAC
  REZ_BACKGROUND = 10001,
#elif WINDOWS
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
  TAG_BEAT_BUTTON,
  TAG_SPLASH
};

#define DEF_ANIMATION_FRAMES 5
#define DEF_ANIMATION_TICKS 8

#define DEF_DOWNSAMPLE 1000 // Downsampling rate
#define DEF_TEMPO 120

#define MIN_AMPLITUDE 0.1 // Used to filter noise
#define MIN_BPM 60
#define MAX_BPM 180 // Helps to improve accuracy

#include "JucePluginCharacteristics.h"