#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <sstream>

/**
 * Simple Point class containing a public unsigned `x` and `y` for representing 2D points on an image.
 */
struct Point {
  unsigned x;
  unsigned y;

  Point() : Point(0, 0) { }
  Point(unsigned x, unsigned y) : x(x), y(y) { }

  bool operator<(const Point &other) const {
    return (x < other.x || y < other.y);
  }

  bool operator==(const Point &other) const {
    return (x == other.x && y == other.y);
  }
};

inline std::ostream & operator<<(std::ostream & out, Point const & point) {
  out << "(" << point.x << ", " << point.y << ")";
  return out;
}

#endif
