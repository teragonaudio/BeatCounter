/*
  ==============================================================================

    EditorViewController.h
    Created: 28 Jan 2013 10:08:12pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __EDITORVIEWCONTROLLER_H_762A743D__
#define __EDITORVIEWCONTROLLER_H_762A743D__

class EditorViewController {
public:
    EditorViewController() {}
    virtual ~EditorViewController() {}

    virtual bool getFilterButtonState() const = 0;
    virtual bool getLinkButtonState() const = 0;

    virtual void onFilterButtonPressed(bool isEnabled) = 0;
    virtual void onLinkButtonPressed(bool isEnabled) = 0;
    virtual void onResetButtonPressed(bool isEnabled) = 0;

    virtual void onEditorClosed() = 0;
};

#endif  // __EDITORVIEWCONTROLLER_H_762A743D__
