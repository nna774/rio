#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.hpp"

void write_color(std::ostream &fs, Color color) {
  // Write the translated [0,255] value of each color component.
  fs << static_cast<int>(255.999 * color.x()) << ' '
     << static_cast<int>(255.999 * color.y()) << ' '
     << static_cast<int>(255.999 * color.z()) << '\n';
}

#endif
