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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainEditorView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainEditorView::MainEditorView (BeatCounterAudioProcessor* ownerFilter, teragon::ThreadsafePluginParameterSet& p, teragon::ResourceCache *r)
    : AudioProcessorEditor(ownerFilter),
      parameters(p),
      resources(r)
{
    addAndMakeVisible (beatIndicatorLight = new teragon::IndicatorLight (parameters,
                                                                         "Beat Triggered",
                                                                         resources));
    beatIndicatorLight->setName ("BeatIndicatorLight");

    addAndMakeVisible (hostTempoButton = new teragon::PushButton (parameters,
                                                                  "Use Host Tempo",
                                                                  resources));
    hostTempoButton->setName ("host tempo button");

    addAndMakeVisible (resetButton = new teragon::ToggleButton (parameters,
                                                                "Reset",
                                                                resources));
    resetButton->setName ("reset button");

    addAndMakeVisible (toleranceKnob = new teragon::ImageKnobLarge (parameters,
                                                                    "Tolerance",
                                                                    resources));
    toleranceKnob->setName ("tolerance knob");

    addAndMakeVisible (autofilterFrequencyKnob = new teragon::ImageKnobSmall (parameters,
                                                                              "Autofilter Frequency",
                                                                              resources));
    autofilterFrequencyKnob->setName ("autofilter frequency knob");

    addAndMakeVisible (autofilterButton = new teragon::PushButton (parameters,
                                                                   "Autofilter",
                                                                   resources));
    autofilterButton->setName ("enable autofilter");

    addAndMakeVisible (currentBpmLabel = new teragon::ParameterLabel());
    currentBpmLabel->setName ("current bpm label");

    addAndMakeVisible (runningBpmLabel = new teragon::ParameterLabel (parameters,
                                                                      "Running BPM"));
    runningBpmLabel->setName ("running bpm label");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (472, 162);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainEditorView::~MainEditorView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    beatIndicatorLight = nullptr;
    hostTempoButton = nullptr;
    resetButton = nullptr;
    toleranceKnob = nullptr;
    autofilterFrequencyKnob = nullptr;
    autofilterButton = nullptr;
    currentBpmLabel = nullptr;
    runningBpmLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    delete resources;
    //[/Destructor]
}

//==============================================================================
void MainEditorView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainEditorView::resized()
{
    beatIndicatorLight->setBounds (191, 104, 24, 24);
    hostTempoButton->setBounds (18, 104, 70, 40);
    resetButton->setBounds (104, 104, 70, 40);
    toleranceKnob->setBounds (341, 18, 113, 113);
    autofilterFrequencyKnob->setBounds (245, 18, 66, 66);
    autofilterButton->setBounds (243, 104, 70, 40);
    currentBpmLabel->setBounds (40, 24, 104, 24);
    runningBpmLabel->setBounds (80, 64, 104, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainEditorView" componentName=""
                 parentClasses="public AudioProcessorEditor" constructorParams="BeatCounterAudioProcessor* ownerFilter, teragon::ThreadsafePluginParameterSet&amp; p, teragon::ResourceCache *r"
                 variableInitialisers="AudioProcessorEditor(ownerFilter),&#10;parameters(p),&#10;resources(r)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="472" initialHeight="162">
  <BACKGROUND backgroundColour="ff000000"/>
  <GENERICCOMPONENT name="BeatIndicatorLight" id="9597f0a11978ce24" memberName="beatIndicatorLight"
                    virtualName="teragon::IndicatorLight" explicitFocusOrder="0"
                    pos="191 104 24 24" class="Component" params="parameters,&#10;&quot;Beat Triggered&quot;,&#10;resources"/>
  <GENERICCOMPONENT name="host tempo button" id="b555149503e7cf17" memberName="hostTempoButton"
                    virtualName="teragon::PushButton" explicitFocusOrder="0" pos="18 104 70 40"
                    class="Component" params="parameters,&#10;&quot;Match Host Tempo&quot;,&#10;resources"/>
  <GENERICCOMPONENT name="reset button" id="d1b29d5dfcb7dd8c" memberName="resetButton"
                    virtualName="teragon::ToggleButton" explicitFocusOrder="0" pos="104 104 70 40"
                    class="Component" params="parameters,&#10;&quot;Reset&quot;,&#10;resources"/>
  <GENERICCOMPONENT name="tolerance knob" id="be48e8e7bba31a8f" memberName="toleranceKnob"
                    virtualName="teragon::ImageKnobLarge" explicitFocusOrder="0"
                    pos="341 18 113 113" class="Component" params="parameters,&#10;&quot;Tolerance&quot;,&#10;resources"/>
  <GENERICCOMPONENT name="autofilter frequency knob" id="326bdbc56dc50049" memberName="autofilterFrequencyKnob"
                    virtualName="teragon::ImageKnobSmall" explicitFocusOrder="0"
                    pos="245 18 66 66" class="Component" params="parameters,&#10;&quot;Autofilter Frequency&quot;,&#10;resources"/>
  <GENERICCOMPONENT name="enable autofilter" id="3734e39975c01330" memberName="autofilterButton"
                    virtualName="teragon::PushButton" explicitFocusOrder="0" pos="243 104 70 40"
                    class="Component" params="parameters,&#10;&quot;Autofilter&quot;,&#10;resources"/>
  <GENERICCOMPONENT name="current bpm label" id="97bbaab7b99b9c83" memberName="currentBpmLabel"
                    virtualName="teragon::ParameterLabel" explicitFocusOrder="0"
                    pos="40 24 104 24" class="Component" params=""/>
  <GENERICCOMPONENT name="running bpm label" id="9e8fda42544a544" memberName="runningBpmLabel"
                    virtualName="teragon::ParameterLabel" explicitFocusOrder="0"
                    pos="80 64 104 24" class="Component" params="parameters,&#10;&quot;Running BPM&quot;"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
