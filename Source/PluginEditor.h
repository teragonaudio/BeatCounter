/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  28 Jan 2013 10:22:48pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_BEATCOUNTEREDITORVIEW_PLUGINEDITOR_4D462327__
#define __JUCER_HEADER_BEATCOUNTEREDITORVIEW_PLUGINEDITOR_4D462327__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "EditorViewController.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class BeatCounterEditorView  : public AudioProcessorEditor,
                               public ButtonListener
{
public:
    //==============================================================================
    BeatCounterEditorView (BeatCounterAudioProcessor* ownerFilter);
    ~BeatCounterEditorView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  void setViewController(EditorViewController* viewController);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* background_png;
    static const int background_pngSize;
    static const char* beatlightAnimation1_png;
    static const int beatlightAnimation1_pngSize;
    static const char* beatlightAnimation2_png;
    static const int beatlightAnimation2_pngSize;
    static const char* beatlightAnimation3_png;
    static const int beatlightAnimation3_pngSize;
    static const char* beatlightAnimation4_png;
    static const int beatlightAnimation4_pngSize;
    static const char* beatlightAnimation5_png;
    static const int beatlightAnimation5_pngSize;
    static const char* filterButtonOff_png;
    static const int filterButtonOff_pngSize;
    static const char* filterButtonOn_png;
    static const int filterButtonOn_pngSize;
    static const char* resetButtonOff_png;
    static const int resetButtonOff_pngSize;
    static const char* resetButtonOn_png;
    static const int resetButtonOn_pngSize;
    static const char* linkButtonOff_png;
    static const int linkButtonOff_pngSize;
    static const char* linkButtonOn_png;
    static const int linkButtonOn_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
  EditorViewController* viewController;
    //[/UserVariables]

    //==============================================================================
    Label* currentBpmLabel;
    Label* currentBpmLabel2;
    ImageButton* beatIndicatorButton;
    ImageButton* filterButton;
    ImageButton* resetButton;
    ImageButton* linkButton;
    Image cachedImage_background_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeatCounterEditorView);
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCER_HEADER_BEATCOUNTEREDITORVIEW_PLUGINEDITOR_4D462327__
