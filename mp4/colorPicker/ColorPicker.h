#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "../cs225/HSLAPixel.h"

using namespace cs225;

class ColorPicker {
public:
  virtual ~ColorPicker() { }
  virtual HSLAPixel getColor(unsigned x, unsigned y) = 0;
};

#endif