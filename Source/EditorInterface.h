/*
  ==============================================================================

    EditorInterface.h
    Created: 12 Feb 2013 9:11:28pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __EDITORINTERFACE_H_FCABD151__
#define __EDITORINTERFACE_H_FCABD151__

class EditorInterface {
public:
    EditorInterface() {}
    virtual ~EditorInterface() {}

    virtual void updateParameter(int index, double value) = 0;
    virtual void updateCurrentBpm(double bpm) const = 0;
    virtual void updateRunningBpm(double bpm) const = 0;
    virtual void triggerBeatLight() = 0;
};

#endif  // __EDITORINTERFACE_H_FCABD151__
