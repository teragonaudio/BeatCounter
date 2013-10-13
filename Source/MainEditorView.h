/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_A1856FAF8960A11E__
#define __JUCE_HEADER_A1856FAF8960A11E__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "BeatCounterAudioProcessor.h"
#include "EditorViewController.h"
#include "EditorInterface.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainEditorView  : public AudioProcessorEditor,
                        public EditorInterface
{
public:
    //==============================================================================
    MainEditorView (BeatCounterAudioProcessor* ownerFilter);
    ~MainEditorView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setViewController(EditorViewController* viewController);
    void updateParameter(int index, double value);
    void updateCurrentBpm(double bpm) const;
    void updateRunningBpm(double bpm) const;

    void triggerBeatLight();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* beatlightAnimation1_png;
    static const int beatlightAnimation1_pngSize;
    static const char* beatlightAnimation5_png;
    static const int beatlightAnimation5_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    EditorViewController* viewController;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> currentBpmLabel;
    ScopedPointer<Label> runningBpmLabel;
    ScopedPointer<ImageComponent> beatIndicatorLight;
    ScopedPointer<Component> hostTempoButton;
    ScopedPointer<Component> resetButton;
    ScopedPointer<Component> toleranceKnob;
    ScopedPointer<Component> lopassFilterFreqKnob;
    ScopedPointer<Component> enableLopassFilterButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainEditorView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_A1856FAF8960A11E__
