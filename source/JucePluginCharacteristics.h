#ifndef __JucePluginCharacteristics_h__
#define __JucePluginCharacteristics_h__

#define JucePlugin_Build_VST    1
#define JucePlugin_Build_AU     1
#define JucePlugin_Build_RTAS   0

#define JucePlugin_Name                 PLUGIN_NAME
#define JucePlugin_Desc                 PLUGIN_NAME
#define JucePlugin_Manufacturer         PLUGIN_MANUFACTURER
#define JucePlugin_ManufacturerCode     PLUGIN_NAME_FOURCC
#define JucePlugin_PluginCode           PLUGIN_MANUFACTURER_FOURCC
#define JucePlugin_MaxNumInputChannels  2
#define JucePlugin_MaxNumOutputChannels 2
#define JucePlugin_PreferredChannelConfigurations   {1, 1}, {2, 2}
#define JucePlugin_IsSynth              0
#define JucePlugin_WantsMidiInput       0
#define JucePlugin_ProducesMidiOutput   1
#define JucePlugin_IsSynth              0
#define JucePlugin_SilenceInProducesSilenceOut  0
#define JucePlugin_TailLengthSeconds    0
#define JucePlugin_EditorRequiresKeyboardFocus  0
#define JucePlugin_VersionCode          VERSION_NUMBER
#define JucePlugin_VersionString        VERSION_STRING
#define JucePlugin_VSTUniqueID          JucePlugin_PluginCode
#define JucePlugin_VSTCategory          kPlugCategEffect
#define JucePlugin_AUMainType           kAudioUnitType_Effect
#define JucePlugin_AUSubType            JucePlugin_PluginCode
#define JucePlugin_AUExportPrefix       BeatCounterAU
#define JucePlugin_AUExportPrefixQuoted "BeatCounterAU"
#define JucePlugin_AUManufacturerCode   JucePlugin_ManufacturerCode
#define JucePlugin_CFBundleIdentifier   org.teragon.BeatCounter
#define JucePlugin_AUCocoaViewClassName BeatCounterAUView
#define JucePlugin_RTASCategory         ePlugInCategory_None
#define JucePlugin_RTASManufacturerCode JucePlugin_ManufacturerCode
#define JucePlugin_RTASProductId        JucePlugin_PluginCode

#define JUCE_USE_VSTSDK_2_4             1

#endif