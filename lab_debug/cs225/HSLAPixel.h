/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 */

#ifndef CS225_HSLAPIXEL_H
#define CS225_HSLAPIXEL_H

namespace cs225 {
  class HSLAPixel {
  public:
    double h; /**< Double for the hue of the pixel, in degrees [0, 360]. */
    double s; /**< Double for the saturation of the pixel, [0, 1]. */
    double l; /**< Double for the luminance of the pixel, [0, 1]. */
    double a; /**< Double for the alpha of the pixel, [0, 1]. */

    bool operator== (HSLAPixel const & other) const {
      if (this->l == 0 && other.l == 0) { return true; }
      else if (this->l == 1 && other.l == 1) { return true; }
      else if (this->a == 0 && other.a == 0) { return true; }
      else {
        return (
          this->h == other.h &&
          this->s == other.s &&
          this->l == other.l &&
          this->a == other.a
        );
      }
    }

    /**
     * Constructs a default HSLAPixel. A default pixel is completely
     * opaque (non-transparent) and white. Opaque implies that the
     * alpha component of the pixel is 1.0. Lower values are
     * transparent.
     */
    HSLAPixel();

    /**
     * Constructs an opaque HSLAPixel with the given hue, saturation,
     * and luminance values. The alpha component of the pixel constructed
     * should be 1.0.
     * @param hue Hue value for the new pixel, in degrees [0, 360].
     * @param saturation Saturation value for the new pixel, [0, 1].
     * @param luminance Luminance value for the new pixel, [0, 1].
     */
    HSLAPixel(double hue, double saturation, double luminance);

    /**
     * Constructs an opaque HSLAPixel with the given hue, saturation,
     * luminance, and alpha values.
     * @param hue Hue value for the new pixel, in degrees [0, 360].
     * @param saturation Saturation value for the new pixel, [0, 1].
     * @param luminance Luminance value for the new pixel, [0, 1].
     * @param alpha Alpha value for the new pixel, [0, 1].
     */
     HSLAPixel(double hue, double saturation, double luminance, double alpha);
  };
}

#endif