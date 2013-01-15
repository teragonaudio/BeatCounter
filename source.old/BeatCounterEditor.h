/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  13 May 2010 8:35:41 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_BEATCOUNTEREDITOR_BEATCOUNTEREDITOR_F04E6779__
#define __JUCER_HEADER_BEATCOUNTEREDITOR_BEATCOUNTEREDITOR_F04E6779__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"

#ifndef __BeatCounter_h__
#include "BeatCounter.h"
#endif

#ifndef __BeatCounterModel_h__
#include "BeatCounterModel.h"
#endif

#ifndef __ImageAnimation_h__
#include "ImageAnimation.h"
#endif

#ifndef __RefreshTextLabelsTimer_h__
#include "RefreshTextLabelsTimer.h"
#endif
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class BeatCounterEditor  : public AudioProcessorEditor,
                           public teragon::RefreshTextLabelsTimerResponder,
                           public ButtonListener
{
public:
    //==============================================================================
    BeatCounterEditor (teragon::BeatCounter* beatCounter);
    ~BeatCounterEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  void onTextLabelsRefresh();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* background_png;
    static const int background_pngSize;
    static const char* about_png;
    static const int about_pngSize;
    static const char* filterButtonOff_png;
    static const int filterButtonOff_pngSize;
    static const char* filterButtonOn_png;
    static const int filterButtonOn_pngSize;
    static const char* linkButtonOff_png;
    static const int linkButtonOff_pngSize;
    static const char* linkButtonOn_png;
    static const int linkButtonOn_pngSize;
    static const char* resetButtonOff_png;
    static const int resetButtonOff_pngSize;
    static const char* resetButtonOn_png;
    static const int resetButtonOn_pngSize;
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

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
  teragon::BeatCounterModel* beatCounterModel;
  teragon::RefreshTextLabelsTimer* refreshBpmDisplayTimer;
    //[/UserVariables]

    //==============================================================================
    ImageButton* filterButton;
    ImageButton* resetButton;
    ImageButton* linkButton;
    Label* currentBpmLabel;
    Label* runningBpmLabel;
    teragon::ImageAnimation* beatLight;
    Image* cachedImage_background_png;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    BeatCounterEditor (const BeatCounterEditor&);
    const BeatCounterEditor& operator= (const BeatCounterEditor&);
};


#endif   // __JUCER_HEADER_BEATCOUNTEREDITOR_BEATCOUNTEREDITOR_F04E6779__
