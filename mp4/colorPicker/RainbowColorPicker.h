#ifndef RAINBOWCOLORPICKER_H
#define RAINBOWCOLORPICKER_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"

using namespace cs225;

class RainbowColorPicker : public ColorPicker {
public:
  RainbowColorPicker(double increment);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  double hue;
  double increment;
};

#endif
