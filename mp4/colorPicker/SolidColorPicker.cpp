#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "SolidColorPicker.h"

using namespace cs225;

SolidColorPicker::SolidColorPicker(HSLAPixel color) : color(color) { }

HSLAPixel SolidColorPicker::getColor(unsigned x, unsigned y) {
  return color;
}
