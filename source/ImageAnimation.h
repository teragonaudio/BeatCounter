/*
 *  ImageAnimation.h
 *  BeatCounter
 *
 *  Created by Nik Reiman on 2010-05-13.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __ImageAnimation_h__
#define __ImageAnimation_h__

#include "juce_amalgamated.h"

namespace teragon {
  class ImageAnimation : public Component {
  public:
    ImageAnimation() {}
    ~ImageAnimation() {}

    void paint(Graphics& g);
    
    void setImages(Image** images, const int numImages);
    void setImage(int index);
    
  private:
    Image* getCurrentImage() { return this->currentImage; }
    
    Image** images;
    Image* currentImage;
    int numImages;
  };
}

#endif
