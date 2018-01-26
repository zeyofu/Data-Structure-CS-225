/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 */

#include "HSLAPixel.h"

namespace cs225 {
  HSLAPixel::HSLAPixel() {
    h = 0;
    s = 0;
    l = 1.0;
    a = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance) {
    h = hue;
    s = saturation;
    l = luminance;
    a = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha) {
    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
  }

  
}
