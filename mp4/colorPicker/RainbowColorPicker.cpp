#include "../cs225/HSLAPixel.h"

#include "ColorPicker.h"
#include "RainbowColorPicker.h"

RainbowColorPicker::RainbowColorPicker(double increment)
  : hue(0), increment(increment) { }

HSLAPixel RainbowColorPicker::getColor(unsigned x, unsigned y) {
  HSLAPixel pixel(hue, 1, 0.5);
  hue += increment;
  if (hue >= 360) { hue -= 360; }
  return pixel;
}
