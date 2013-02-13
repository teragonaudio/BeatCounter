/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  13 Feb 2013 10:45:08pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MAINEDITORVIEW_MAINEDITORVIEW_FABA8614__
#define __JUCER_HEADER_MAINEDITORVIEW_MAINEDITORVIEW_FABA8614__

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
                        public EditorInterface,
                        public ButtonListener,
                        public SliderListener
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
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);

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
    Label* currentBpmLabel;
    Label* runningBpmLabel;
    ImageComponent* beatIndicatorLight;
    TextButton* resetButton;
    ToggleButton* filterButton;
    ToggleButton* linkButton;
    Slider* toleranceSlider;
    Slider* filterFrequencySlider;
    Image cachedImage_beatlightAnimation1_png;
    Image cachedImage_beatlightAnimation5_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainEditorView);
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCER_HEADER_MAINEDITORVIEW_MAINEDITORVIEW_FABA8614__
