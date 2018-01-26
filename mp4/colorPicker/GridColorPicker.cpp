#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "GridColorPicker.h"

using namespace cs225;

GridColorPicker::GridColorPicker(
  HSLAPixel gridColor, HSLAPixel backgroundColor, unsigned spacing
) : gridColor(gridColor), backgroundColor(backgroundColor), spacing(spacing) { }

HSLAPixel GridColorPicker::getColor(unsigned x, unsigned y) {
  if (x % spacing == 0 || y % spacing == 0) {
    return gridColor;
  } else {
    return backgroundColor;
  }
}
