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
    addAndMakeVisible (currentBpmLabel = new Label ("Current BPM Label",
                                                    "---.--"));
    currentBpmLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 24.00f, Font::plain));
    currentBpmLabel->setJustificationType (Justification::centredLeft);
    currentBpmLabel->setEditable (false, false, false);
    currentBpmLabel->setColour (TextEditor::textColourId, Colours::black);
    currentBpmLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (runningBpmLabel = new Label ("Running BPM Label",
                                                    "---.--"));
    runningBpmLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 24.00f, Font::plain));
    runningBpmLabel->setJustificationType (Justification::centredLeft);
    runningBpmLabel->setEditable (false, false, false);
    runningBpmLabel->setColour (TextEditor::textColourId, Colours::black);
    runningBpmLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (beatIndicatorLight = new teragon::IndicatorLight (parameters,
                                                                         "Beat Triggered",
                                                                         resources));
    beatIndicatorLight->setName ("BeatIndicatorLight");

    addAndMakeVisible (hostTempoButton = new teragon::PushButton (parameters,
                                                                  "Match Host Tempo",
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

    currentBpmLabel = nullptr;
    runningBpmLabel = nullptr;
    beatIndicatorLight = nullptr;
    hostTempoButton = nullptr;
    resetButton = nullptr;
    toleranceKnob = nullptr;
    autofilterFrequencyKnob = nullptr;
    autofilterButton = nullptr;


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
    currentBpmLabel->setBounds (104, 24, 88, 24);
    runningBpmLabel->setBounds (104, 56, 88, 24);
    beatIndicatorLight->setBounds (191, 104, 24, 24);
    hostTempoButton->setBounds (18, 104, 70, 40);
    resetButton->setBounds (104, 104, 70, 40);
    toleranceKnob->setBounds (341, 18, 113, 113);
    autofilterFrequencyKnob->setBounds (245, 18, 66, 66);
    autofilterButton->setBounds (243, 104, 70, 40);
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
  <LABEL name="Current BPM Label" id="4e3ed08c8c5358ee" memberName="currentBpmLabel"
         virtualName="" explicitFocusOrder="0" pos="104 24 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="---.--" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="24"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Running BPM Label" id="bb007035ee015793" memberName="runningBpmLabel"
         virtualName="" explicitFocusOrder="0" pos="104 56 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="---.--" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="24"
         bold="0" italic="0" justification="33"/>
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
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
