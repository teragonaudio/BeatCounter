#ifndef __JucePluginCharacteristics_h__
#define __JucePluginCharacteristics_h__

#define JucePlugin_Build_VST    1
#define JucePlugin_Build_AU     1
#define JucePlugin_Build_RTAS   0

#define JucePlugin_Name                 "BeatCounter"
#define JucePlugin_Desc                 "BeatCounter"
#define JucePlugin_Manufacturer         "Teragon Audio"
#define JucePlugin_ManufacturerCode     'Tera'
#define JucePlugin_PluginCode           'BtCt'
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
#define JucePlugin_VersionCode          0x020000
#define JucePlugin_VersionString        "2.0.0"
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

#define JUCE_ObjCExtraSuffix            201004071913
#define JUCE_USE_VSTSDK_2_4             1

#endif
