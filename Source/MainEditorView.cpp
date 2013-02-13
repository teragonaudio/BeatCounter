/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  13 Feb 2013 10:07:57pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainEditorView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
static const int kNumDecimalPlaces = 2;
//[/MiscUserDefs]

//==============================================================================
MainEditorView::MainEditorView (BeatCounterAudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter),
      EditorInterface(),
      currentBpmLabel (0),
      runningBpmLabel (0),
      beatIndicatorLight (0),
      resetButton (0),
      filterButton (0),
      linkButton (0),
      toleranceSlider (0),
      slider (0),
      cachedImage_beatlightAnimation1_png (0),
      cachedImage_beatlightAnimation5_png (0)
{
    addAndMakeVisible (currentBpmLabel = new Label ("Current BPM Label",
                                                    "---.--"));
    currentBpmLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 24.0000f, Font::plain));
    currentBpmLabel->setJustificationType (Justification::centredLeft);
    currentBpmLabel->setEditable (false, false, false);
    currentBpmLabel->setColour (TextEditor::textColourId, Colours::black);
    currentBpmLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (runningBpmLabel = new Label ("Running BPM Label",
                                                    "---.--"));
    runningBpmLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 24.0000f, Font::plain));
    runningBpmLabel->setJustificationType (Justification::centredLeft);
    runningBpmLabel->setEditable (false, false, false);
    runningBpmLabel->setColour (TextEditor::textColourId, Colours::black);
    runningBpmLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (beatIndicatorLight = new ImageComponent());
    beatIndicatorLight->setName ("BeatIndicatorLight");

    addAndMakeVisible (resetButton = new TextButton ("Reset Button"));
    resetButton->setButtonText ("Reset");
    resetButton->addListener (this);
    resetButton->setColour (TextButton::buttonColourId, Colour (0xff2c4680));
    resetButton->setColour (TextButton::buttonOnColourId, Colour (0xff1c3670));
    resetButton->setColour (TextButton::textColourOnId, Colours::white);
    resetButton->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (filterButton = new ToggleButton ("Filter Button"));
    filterButton->setButtonText ("Lowpass Filter Enabled");
    filterButton->addListener (this);
    filterButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (linkButton = new ToggleButton ("Link Button"));
    linkButton->setButtonText ("Link to Host\'s Tempo");
    linkButton->addListener (this);
    linkButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (toleranceSlider = new Slider ("Tolerance Slider"));
    toleranceSlider->setRange (0, 100, 1);
    toleranceSlider->setSliderStyle (Slider::LinearHorizontal);
    toleranceSlider->setTextBoxStyle (Slider::TextBoxRight, false, 34, 20);
    toleranceSlider->setColour (Slider::thumbColourId, Colour (0xff2c4680));
    toleranceSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    toleranceSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xffabb699));
    toleranceSlider->setColour (Slider::textBoxOutlineColourId, Colour (0xb2000000));
    toleranceSlider->addListener (this);

    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (50, 400, 1);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::TextBoxRight, false, 34, 20);
    slider->setColour (Slider::thumbColourId, Colour (0xff2c4680));
    slider->setColour (Slider::textBoxBackgroundColourId, Colour (0xffabb699));
    slider->setColour (Slider::textBoxOutlineColourId, Colour (0xb2000000));
    slider->addListener (this);

    cachedImage_beatlightAnimation1_png = ImageCache::getFromMemory (beatlightAnimation1_png, beatlightAnimation1_pngSize);
    cachedImage_beatlightAnimation5_png = ImageCache::getFromMemory (beatlightAnimation5_png, beatlightAnimation5_pngSize);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (205, 264);


    //[Constructor] You can add your own custom stuff here..
    filterButton->setColour (TextButton::buttonColourId, Colour (0xff2c4680));
    filterButton->setColour (TextButton::buttonOnColourId, Colour (0xff2c4680));
    linkButton->setColour (TextButton::buttonColourId, Colour (0xff2c4680));
    linkButton->setColour (TextButton::buttonOnColourId, Colour (0xff2c4680));
    //[/Constructor]
}

MainEditorView::~MainEditorView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (currentBpmLabel);
    deleteAndZero (runningBpmLabel);
    deleteAndZero (beatIndicatorLight);
    deleteAndZero (resetButton);
    deleteAndZero (filterButton);
    deleteAndZero (linkButton);
    deleteAndZero (toleranceSlider);
    deleteAndZero (slider);


    //[Destructor]. You can add your own custom destruction code here..
    viewController->onEditorClosed();
    //[/Destructor]
}

//==============================================================================
void MainEditorView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff757c8a));

    g.setColour (Colours::black);
    g.drawImage (cachedImage_beatlightAnimation1_png,
                 174, 96, 25, 25,
                 0, 0, cachedImage_beatlightAnimation1_png.getWidth(), cachedImage_beatlightAnimation1_png.getHeight());

    g.setColour (Colours::black.withAlpha (0.0010f));
    g.drawImage (cachedImage_beatlightAnimation5_png,
                 174, 96, 25, 25,
                 0, 0, cachedImage_beatlightAnimation5_png.getWidth(), cachedImage_beatlightAnimation5_png.getHeight());

    g.setColour (Colour (0xffabb699));
    g.fillRoundedRectangle (5.0f, 5.0f, 195.0f, 84.0f, 10.0000f);

    g.setColour (Colours::black);
    g.drawRoundedRectangle (5.0f, 5.0f, 195.0f, 84.0f, 10.0000f, 0.6000f);

    g.setColour (Colours::black);
    g.setFont (Font (16.0000f, Font::plain));
    g.drawText ("Current BPM:",
                13, 19, 107, 24,
                Justification::centredLeft, true);

    g.setColour (Colours::black);
    g.setFont (Font (16.0000f, Font::plain));
    g.drawText ("Running BPM:",
                13, 51, 107, 24,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.0000f, Font::plain));
    g.drawText ("Beat",
                134, 96, 48, 25,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.0000f, Font::plain));
    g.drawText ("Detection Tolerance",
                7, 124, 161, 23,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.0000f, Font::plain));
    g.drawText ("Lowpass Filter Frequency",
                7, 215, 161, 24,
                Justification::centredLeft, true);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainEditorView::resized()
{
    currentBpmLabel->setBounds (108, 19, 88, 24);
    runningBpmLabel->setBounds (108, 52, 88, 24);
    beatIndicatorLight->setBounds (174, 96, 25, 25);
    resetButton->setBounds (6, 96, 96, 24);
    filterButton->setBounds (2, 191, 198, 24);
    linkButton->setBounds (2, 166, 198, 24);
    toleranceSlider->setBounds (4, 142, 196, 24);
    slider->setBounds (4, 236, 196, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainEditorView::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    bool isEnabled = buttonThatWasClicked->isDown();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == resetButton)
    {
        //[UserButtonCode_resetButton] -- add your button handler code here..
        viewController->onResetButtonPressed(isEnabled);
        //[/UserButtonCode_resetButton]
    }
    else if (buttonThatWasClicked == filterButton)
    {
        //[UserButtonCode_filterButton] -- add your button handler code here..
        viewController->onFilterButtonPressed(isEnabled);
        //[/UserButtonCode_filterButton]
    }
    else if (buttonThatWasClicked == linkButton)
    {
        //[UserButtonCode_linkButton] -- add your button handler code here..
        viewController->onLinkButtonPressed(isEnabled);
        //[/UserButtonCode_linkButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainEditorView::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == toleranceSlider)
    {
        //[UserSliderCode_toleranceSlider] -- add your slider handling code here..
        //[/UserSliderCode_toleranceSlider]
    }
    else if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainEditorView::setViewController(EditorViewController* viewController) {
    this->viewController = viewController;
    filterButton->setToggleState(viewController->getFilterButtonState(), false);
    linkButton->setToggleState(viewController->getLinkButtonState(), false);
}

void MainEditorView::updateCurrentBpm(double bpm) const {
    if (bpm > 0.0) {
        String currentBpm(bpm, kNumDecimalPlaces);
        currentBpmLabel->setText(currentBpm, false);
    }
    else {
        currentBpmLabel->setText("---.--", false);
    }
}

void MainEditorView::updateRunningBpm(double bpm) const {
    if (bpm > 0.0) {
        String runningBpm(bpm, kNumDecimalPlaces);
        runningBpmLabel->setText(runningBpm, false);
    }
    else {
        runningBpmLabel->setText("---.--", false);
    }
}

void MainEditorView::triggerBeatLight() {
    beatIndicatorLight->setImage(cachedImage_beatlightAnimation5_png);
    beatIndicatorLight->setVisible(true);
    beatIndicatorLight->setAlpha(1.0);
    ComponentAnimator &animator = Desktop::getInstance().getAnimator();
    animator.fadeOut(beatIndicatorLight, 250);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainEditorView" componentName=""
                 parentClasses="public AudioProcessorEditor, public EditorInterface"
                 constructorParams="BeatCounterAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter),&#10;EditorInterface()"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="205" initialHeight="264">
  <BACKGROUND backgroundColour="ff757c8a">
    <IMAGE pos="174 96 25 25" resource="beatlightAnimation1_png" opacity="1"
           mode="0"/>
    <IMAGE pos="174 96 25 25" resource="beatlightAnimation5_png" opacity="0.001"
           mode="0"/>
    <ROUNDRECT pos="5 5 195 84" cornerSize="10" fill="solid: ffabb699" hasStroke="1"
               stroke="0.600000024, mitered, butt" strokeColour="solid: ff000000"/>
    <TEXT pos="13 19 107 24" fill="solid: ff000000" hasStroke="0" text="Current BPM:"
          fontname="Default font" fontsize="16" bold="0" italic="0" justification="33"/>
    <TEXT pos="13 51 107 24" fill="solid: ff000000" hasStroke="0" text="Running BPM:"
          fontname="Default font" fontsize="16" bold="0" italic="0" justification="33"/>
    <TEXT pos="134 96 48 25" fill="solid: ffffffff" hasStroke="0" text="Beat"
          fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
    <TEXT pos="7 124 161 23" fill="solid: ffffffff" hasStroke="0" text="Detection Tolerance"
          fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
    <TEXT pos="7 215 161 24" fill="solid: ffffffff" hasStroke="0" text="Lowpass Filter Frequency"
          fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  </BACKGROUND>
  <LABEL name="Current BPM Label" id="4e3ed08c8c5358ee" memberName="currentBpmLabel"
         virtualName="" explicitFocusOrder="0" pos="108 19 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="---.--" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="24"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Running BPM Label" id="bb007035ee015793" memberName="runningBpmLabel"
         virtualName="" explicitFocusOrder="0" pos="108 52 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="---.--" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="24"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="BeatIndicatorLight" id="9597f0a11978ce24" memberName="beatIndicatorLight"
                    virtualName="" explicitFocusOrder="0" pos="174 96 25 25" class="ImageComponent"
                    params=""/>
  <TEXTBUTTON name="Reset Button" id="c44d9ebbcb52458c" memberName="resetButton"
              virtualName="" explicitFocusOrder="0" pos="6 96 96 24" bgColOff="ff2c4680"
              bgColOn="ff1c3670" textCol="ffffffff" textColOn="ffffffff" buttonText="Reset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="Filter Button" id="f7f8b055ff912d0a" memberName="filterButton"
                virtualName="" explicitFocusOrder="0" pos="2 191 198 24" txtcol="ffffffff"
                buttonText="Lowpass Filter Enabled" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="Link Button" id="8234fc575ae36161" memberName="linkButton"
                virtualName="" explicitFocusOrder="0" pos="2 166 198 24" txtcol="ffffffff"
                buttonText="Link to Host's Tempo" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="Tolerance Slider" id="591bc48bb9446e8a" memberName="toleranceSlider"
          virtualName="" explicitFocusOrder="0" pos="4 142 196 24" thumbcol="ff2c4680"
          textboxtext="ff000000" textboxbkgd="ffabb699" textboxoutline="b2000000"
          min="0" max="100" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="34" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="cf032ec8836f6fa4" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="4 236 196 24" thumbcol="ff2c4680"
          textboxbkgd="ffabb699" textboxoutline="b2000000" min="50" max="400"
          int="1" style="LinearHorizontal" textBoxPos="TextBoxRight" textBoxEditable="1"
          textBoxWidth="34" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: beatlightAnimation1_png, 1462, "../Graphics/beatlightAnimation1.png"
static const unsigned char resource_MainEditorView_beatlightAnimation1_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,25,0,0,0,25,8,2,0,0,0,75,139,18,52,0,0,2,238,105,67,67,80,73,67,67,
32,80,114,111,102,105,108,101,0,0,120,1,133,84,207,107,19,65,20,254,54,110,169,208,34,8,90,107,14,178,120,144,34,73,89,171,104,69,212,54,253,17,98,107,12,219,31,182,69,144,100,51,73,214,110,54,235,238,
38,181,165,136,228,226,209,42,222,69,237,161,7,255,128,30,122,240,100,47,74,133,90,69,40,222,171,40,98,161,23,45,241,205,110,76,182,165,234,192,206,126,243,222,55,239,125,111,118,223,0,13,114,210,52,245,
128,4,228,13,199,82,162,17,105,108,124,66,106,252,136,0,142,162,9,65,52,37,85,219,236,78,36,6,65,131,115,249,123,231,216,122,15,129,91,86,195,123,251,119,178,119,173,154,210,182,154,7,132,253,64,224,71,
154,217,42,176,239,23,113,10,89,18,2,136,60,223,161,41,199,116,8,223,227,216,242,236,143,57,78,121,120,193,181,15,43,61,196,89,34,124,64,53,45,206,127,77,184,83,205,37,211,64,131,72,56,148,245,113,82,
62,156,215,139,148,215,29,7,105,110,102,198,200,16,189,79,144,166,187,204,238,171,98,161,156,78,246,14,144,189,157,244,126,78,179,222,62,194,33,194,11,25,173,63,70,184,141,158,245,140,213,63,226,97,225,
164,230,196,134,61,28,24,53,244,248,96,21,183,26,169,248,53,194,20,95,16,77,39,162,84,113,217,46,13,241,152,174,253,86,242,74,130,112,144,56,202,100,97,128,115,90,72,79,215,76,110,248,186,135,5,125,38,
215,19,175,226,119,86,81,225,121,143,19,103,222,212,221,239,69,218,2,175,48,14,29,12,26,12,154,13,72,80,16,69,4,97,152,176,80,64,134,60,26,49,52,178,114,63,35,171,6,27,147,123,50,117,36,106,187,116,98,
68,177,65,123,54,220,61,183,81,164,221,60,254,40,34,113,148,67,181,8,146,252,65,254,42,175,201,79,229,121,249,203,92,176,216,86,247,148,173,155,154,186,242,224,59,197,229,153,185,26,30,215,211,200,227,
115,77,94,124,149,212,118,147,87,71,150,172,121,122,188,154,236,26,63,236,87,151,49,230,130,53,143,196,115,176,251,241,45,95,149,204,151,41,140,20,197,227,85,243,234,75,132,117,90,49,55,223,159,108,127,
59,61,226,46,207,46,181,214,115,173,137,139,55,86,155,151,103,253,106,72,251,238,170,188,147,230,85,249,79,94,245,241,252,103,205,196,99,226,41,49,38,118,138,231,33,137,151,197,46,241,146,216,75,171,11,
226,96,109,199,8,157,149,134,41,210,109,145,250,36,213,96,96,154,188,245,47,93,63,91,120,189,70,127,12,245,81,148,25,204,210,84,137,247,127,194,42,100,52,157,185,14,111,250,143,219,199,252,23,228,247,
138,231,159,40,2,47,108,224,200,153,186,109,83,113,239,16,161,101,165,110,115,174,2,23,191,209,125,240,182,110,107,163,126,56,252,4,88,60,171,22,173,82,53,159,32,188,1,28,118,135,122,30,232,41,152,211,
150,150,205,57,82,135,44,159,147,186,233,202,98,82,204,80,219,67,82,82,215,37,215,101,75,22,179,153,85,98,233,118,216,153,211,29,110,28,161,57,66,247,196,167,74,101,147,250,175,241,17,176,253,176,82,249,
249,172,82,217,126,78,26,214,129,151,250,111,192,188,253,69,192,120,139,137,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,2,110,73,68,65,84,56,17,229,148,75,111,18,81,20,199,231,253,96,
24,121,164,40,180,72,107,211,69,99,98,161,161,234,78,27,211,13,11,86,108,52,36,46,220,224,55,240,147,241,13,216,177,235,134,198,170,88,1,25,132,121,32,116,30,119,102,24,15,162,195,180,189,139,46,186,235,
205,36,115,238,185,231,252,238,61,255,251,32,63,124,252,68,220,81,163,238,136,179,196,220,7,22,131,211,43,64,142,51,53,212,145,50,80,39,35,243,114,182,88,248,52,205,196,36,57,149,206,100,30,229,18,201,
13,158,23,40,234,186,62,24,22,128,198,99,165,247,253,243,120,52,116,144,237,185,174,235,185,65,16,112,172,106,232,19,219,54,131,69,0,80,94,16,72,242,10,14,195,154,254,214,250,63,190,42,195,190,109,153,
176,34,81,20,25,134,182,129,97,94,194,231,123,30,195,176,162,36,49,44,203,48,36,65,192,247,175,93,1,175,124,218,228,151,58,30,2,136,32,130,66,161,80,169,84,202,229,114,44,22,163,105,26,2,116,93,237,247,
190,153,243,249,127,194,250,143,97,205,103,134,101,154,8,161,108,46,91,175,215,171,213,106,169,84,18,4,33,76,130,218,149,97,143,227,120,138,90,210,195,134,97,185,8,121,30,162,105,42,191,149,175,213,106,
173,86,171,217,108,206,102,179,48,7,140,241,104,16,143,75,80,101,212,121,165,179,26,32,73,26,212,6,165,58,157,78,163,209,232,118,187,147,201,196,255,219,194,76,67,87,229,184,4,93,199,65,161,19,195,18,
68,145,36,73,207,243,52,77,107,183,219,139,197,2,236,48,97,101,64,128,36,197,44,219,142,250,49,53,202,15,146,98,108,57,39,44,5,84,187,9,130,161,108,110,83,20,65,193,245,38,130,19,195,74,166,55,50,15,115,
209,9,111,218,7,197,67,16,20,38,139,14,97,88,137,68,122,255,105,105,51,191,29,141,139,218,207,14,138,199,111,78,160,64,228,174,197,130,0,12,139,101,185,220,86,225,249,203,87,59,187,123,81,196,202,46,150,
14,223,190,123,47,73,9,77,155,34,199,141,6,96,180,135,35,74,81,204,238,222,254,246,206,147,243,179,211,47,231,103,138,242,19,132,201,63,46,28,29,189,120,125,124,66,115,252,197,197,192,48,166,176,215,81,
22,137,125,87,225,222,114,28,43,203,241,116,42,145,78,37,227,178,196,179,28,236,29,212,165,106,250,80,25,27,186,225,32,20,4,81,20,129,93,23,1,231,0,14,142,239,79,45,203,210,244,41,207,177,112,129,64,105,
203,70,150,109,161,229,144,127,13,4,84,60,11,6,224,97,88,190,15,174,55,159,195,197,188,85,195,104,127,171,60,92,208,125,96,253,1,196,147,33,96,180,4,126,46,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* MainEditorView::beatlightAnimation1_png = (const char*) resource_MainEditorView_beatlightAnimation1_png;
const int MainEditorView::beatlightAnimation1_pngSize = 1462;

// JUCER_RESOURCE: beatlightAnimation5_png, 1920, "../Graphics/beatlightAnimation5.png"
static const unsigned char resource_MainEditorView_beatlightAnimation5_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,25,0,0,0,25,8,2,0,0,0,75,139,18,52,0,0,2,238,105,67,67,80,73,67,67,
32,80,114,111,102,105,108,101,0,0,120,1,133,84,207,107,19,65,20,254,54,110,169,208,34,8,90,107,14,178,120,144,34,73,89,171,104,69,212,54,253,17,98,107,12,219,31,182,69,144,100,51,73,214,110,54,235,238,
38,181,165,136,228,226,209,42,222,69,237,161,7,255,128,30,122,240,100,47,74,133,90,69,40,222,171,40,98,161,23,45,241,205,110,76,182,165,234,192,206,126,243,222,55,239,125,111,118,223,0,13,114,210,52,245,
128,4,228,13,199,82,162,17,105,108,124,66,106,252,136,0,142,162,9,65,52,37,85,219,236,78,36,6,65,131,115,249,123,231,216,122,15,129,91,86,195,123,251,119,178,119,173,154,210,182,154,7,132,253,64,224,71,
154,217,42,176,239,23,113,10,89,18,2,136,60,223,161,41,199,116,8,223,227,216,242,236,143,57,78,121,120,193,181,15,43,61,196,89,34,124,64,53,45,206,127,77,184,83,205,37,211,64,131,72,56,148,245,113,82,
62,156,215,139,148,215,29,7,105,110,102,198,200,16,189,79,144,166,187,204,238,171,98,161,156,78,246,14,144,189,157,244,126,78,179,222,62,194,33,194,11,25,173,63,70,184,141,158,245,140,213,63,226,97,225,
164,230,196,134,61,28,24,53,244,248,96,21,183,26,169,248,53,194,20,95,16,77,39,162,84,113,217,46,13,241,152,174,253,86,242,74,130,112,144,56,202,100,97,128,115,90,72,79,215,76,110,248,186,135,5,125,38,
215,19,175,226,119,86,81,225,121,143,19,103,222,212,221,239,69,218,2,175,48,14,29,12,26,12,154,13,72,80,16,69,4,97,152,176,80,64,134,60,26,49,52,178,114,63,35,171,6,27,147,123,50,117,36,106,187,116,98,
68,177,65,123,54,220,61,183,81,164,221,60,254,40,34,113,148,67,181,8,146,252,65,254,42,175,201,79,229,121,249,203,92,176,216,86,247,148,173,155,154,186,242,224,59,197,229,153,185,26,30,215,211,200,227,
115,77,94,124,149,212,118,147,87,71,150,172,121,122,188,154,236,26,63,236,87,151,49,230,130,53,143,196,115,176,251,241,45,95,149,204,151,41,140,20,197,227,85,243,234,75,132,117,90,49,55,223,159,108,127,
59,61,226,46,207,46,181,214,115,173,137,139,55,86,155,151,103,253,106,72,251,238,170,188,147,230,85,249,79,94,245,241,252,103,205,196,99,226,41,49,38,118,138,231,33,137,151,197,46,241,146,216,75,171,11,
226,96,109,199,8,157,149,134,41,210,109,145,250,36,213,96,96,154,188,245,47,93,63,91,120,189,70,127,12,245,81,148,25,204,210,84,137,247,127,194,42,100,52,157,185,14,111,250,143,219,199,252,23,228,247,
138,231,159,40,2,47,108,224,200,153,186,109,83,113,239,16,161,101,165,110,115,174,2,23,191,209,125,240,182,110,107,163,126,56,252,4,88,60,171,22,173,82,53,159,32,188,1,28,118,135,122,30,232,41,152,211,
150,150,205,57,82,135,44,159,147,186,233,202,98,82,204,80,219,67,82,82,215,37,215,101,75,22,179,153,85,98,233,118,216,153,211,29,110,28,161,57,66,247,196,167,74,101,147,250,175,241,17,176,253,176,82,249,
249,172,82,217,126,78,26,214,129,151,250,111,192,188,253,69,192,120,139,137,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,4,56,73,68,65,84,56,17,101,149,221,114,28,53,16,133,213,250,153,
153,253,115,140,13,69,124,65,85,94,135,215,224,130,226,13,120,41,174,40,94,8,168,10,84,72,98,175,189,179,59,163,223,124,173,13,228,130,169,177,74,171,145,142,186,79,159,211,150,31,126,250,185,137,24,99,
154,17,38,188,181,143,77,220,117,133,79,255,61,210,42,91,165,21,105,205,182,198,40,70,71,54,48,250,43,80,21,203,50,43,0,85,235,249,89,29,43,252,212,81,177,244,152,177,96,129,82,44,19,83,139,2,25,64,185,
128,207,226,117,155,70,196,104,171,181,197,185,106,93,177,140,28,9,213,10,235,138,197,61,28,171,213,213,100,185,168,22,203,61,69,39,236,100,157,175,138,197,129,126,63,135,61,88,201,13,197,249,236,130,
226,246,0,1,33,98,78,18,130,43,131,47,209,151,228,53,172,194,113,203,104,197,213,166,233,104,178,34,0,101,175,16,201,15,49,140,41,92,17,135,70,104,226,224,72,131,42,201,149,172,59,210,218,76,172,194,156,
91,26,15,56,202,23,28,245,64,20,104,237,40,103,9,167,53,62,175,47,203,186,228,82,155,181,194,86,49,211,48,238,134,112,240,110,23,70,78,141,0,249,102,138,210,223,76,101,218,201,134,35,178,227,190,97,154,
173,127,138,241,120,89,215,90,218,254,190,109,15,50,76,21,94,226,154,150,57,213,4,57,45,132,189,144,29,60,107,226,252,25,114,236,113,193,148,203,78,83,91,135,233,37,165,99,170,75,152,204,253,131,189,123,
109,183,7,67,221,40,92,140,245,124,90,159,223,63,175,39,111,155,135,114,85,70,37,119,8,135,81,79,213,154,211,10,42,83,97,72,97,60,45,9,80,185,123,112,15,111,236,238,198,142,147,210,17,83,155,178,219,236,
235,102,23,143,239,230,56,79,101,9,173,246,34,88,69,104,142,28,77,161,184,86,171,6,107,228,24,229,210,94,221,217,111,191,179,55,95,125,125,183,255,254,245,244,235,219,229,248,98,77,65,107,142,74,145,207,
229,228,115,155,106,171,37,197,98,115,129,112,45,104,87,35,113,81,8,210,84,77,77,59,185,185,151,237,205,48,109,126,124,179,133,181,211,90,141,117,198,121,241,206,132,96,134,109,153,54,229,112,91,199,73,
69,67,174,170,240,207,90,85,185,170,208,201,219,121,51,110,101,179,55,214,127,179,53,79,41,255,242,123,172,149,75,113,150,131,30,36,217,202,166,201,146,55,94,134,81,79,117,73,97,1,213,170,249,236,18,77,
129,15,50,110,140,15,34,242,207,185,254,246,55,64,186,134,73,250,54,105,139,107,17,201,237,235,96,136,84,101,252,239,243,101,70,100,8,146,117,231,61,64,240,189,198,242,199,99,214,157,221,189,58,230,214,
146,46,136,13,148,145,58,114,74,127,247,135,82,94,237,174,22,65,193,216,205,59,144,138,250,3,125,49,22,108,140,32,149,232,22,185,2,143,55,235,252,216,178,228,72,253,136,153,155,65,243,156,87,235,163,109,
45,112,196,37,99,171,89,76,226,20,245,209,115,236,19,196,221,214,86,231,174,114,35,195,214,78,113,150,184,90,53,185,202,149,118,132,49,140,195,177,21,163,13,234,181,184,76,97,69,227,181,101,110,169,137,
172,61,17,180,5,11,43,34,233,251,81,110,135,203,248,238,189,44,23,117,104,77,68,3,142,7,24,104,36,129,234,2,98,113,190,174,167,118,30,36,12,160,102,248,72,165,158,93,203,136,71,144,151,31,221,171,205,
249,230,248,167,60,126,240,241,226,75,143,139,22,82,11,117,212,236,104,67,36,56,36,85,10,47,12,88,83,3,74,220,223,150,221,20,125,40,23,173,199,16,242,65,30,15,31,223,250,15,127,185,249,24,226,170,180,
16,75,239,145,24,11,25,107,99,163,1,6,109,35,4,75,61,96,48,249,245,146,231,39,76,147,221,88,77,224,216,120,62,141,243,199,48,63,135,203,203,16,151,144,225,151,179,250,114,191,215,18,160,194,66,225,20,
133,7,116,22,225,174,196,37,207,47,106,9,75,255,2,157,216,179,207,107,72,235,128,101,115,239,136,57,127,137,11,60,34,236,53,205,166,139,233,218,70,56,214,251,234,5,101,179,5,222,180,214,181,112,107,247,
179,70,228,115,214,136,104,33,90,233,30,151,54,31,136,82,214,50,149,2,186,183,208,76,56,255,239,247,10,87,123,44,125,162,241,246,60,152,168,135,52,52,44,135,49,52,93,144,186,47,157,214,31,235,106,41,250,
195,39,94,189,169,55,254,107,68,124,187,18,207,22,229,139,221,29,14,198,212,123,168,92,83,106,116,17,3,214,21,72,71,42,172,42,231,255,149,114,113,13,7,160,235,6,112,62,1,42,7,65,174,50,62,29,247,0,0,0,
0,73,69,78,68,174,66,96,130,0,0};

const char* MainEditorView::beatlightAnimation5_png = (const char*) resource_MainEditorView_beatlightAnimation5_png;
const int MainEditorView::beatlightAnimation5_pngSize = 1920;



//[EndFile] You can add extra defines here...
//[/EndFile]
