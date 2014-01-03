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
/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "TeragonGuiComponents.h"
#include "Resources.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainEditorView  : public AudioProcessorEditor
{
public:
    //==============================================================================
    MainEditorView (BeatCounterAudioProcessor* ownerFilter, teragon::ConcurrentParameterSet& p, teragon::ResourceCache *r);
    ~MainEditorView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* background_png;
    static const int background_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    teragon::ConcurrentParameterSet &parameters;
    teragon::ResourceCache *resources;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<teragon::IndicatorLight> beatIndicatorLight;
    ScopedPointer<teragon::PushButton> hostTempoButton;
    ScopedPointer<teragon::ToggleButton> resetButton;
    ScopedPointer<teragon::ImageKnobLarge> toleranceKnob;
    ScopedPointer<teragon::ImageKnobSmall> autofilterFrequencyKnob;
    ScopedPointer<teragon::PushButton> autofilterButton;
    ScopedPointer<teragon::ParameterLabel> currentBpmLabel;
    ScopedPointer<teragon::ParameterLabel> runningBpmLabel;
    ScopedPointer<teragon::ImageKnobLarge> periodKnob;
    ScopedPointer<teragon::StatusBar> statusBar;
    ScopedPointer<teragon::ParameterLabel> versionLabel;
    Image cachedImage_background_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainEditorView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_A1856FAF8960A11E__
