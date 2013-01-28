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

  virtual void onFilterButtonPressed() = 0;
  virtual void onLinkButtonPressed() = 0;
  virtual void onResetButtonPressed() = 0;
};

#endif  // __EDITORVIEWCONTROLLER_H_762A743D__
