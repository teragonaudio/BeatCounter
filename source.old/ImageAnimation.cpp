/*
 *  ImageAnimation.cpp
 *  BeatCounter
 *
 *  Created by Nik Reiman on 2010-05-13.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __ImageAnimation_h__
#include "ImageAnimation.h"
#endif

namespace teragon {
  void ImageAnimation::paint(Graphics& g) {
    Image* image = getCurrentImage();
    const int imageW = image->getWidth();
    const int imageH = image->getHeight();
    g.drawImage(image, 0, 0, imageW, imageH, 0, 0, imageW, imageH, false);
  }
  
  void ImageAnimation::setImages(Image** images, const int numImages) {
    this->images = images;
    this->numImages = numImages;
    setImage(0);
  }

  void ImageAnimation::setImage(int index) {
    if(index >= 0 && index < this->numImages) {
      this->currentImage = this->images[index];
      repaint();
    }
  }
}
