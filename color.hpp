#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.hpp"

void write_color(std::ostream &fs, Color color, int samples_per_pixel) {
  auto r = color.x();
  auto g = color.y();
  auto b = color.z();

  // Divide the color by the number of samples and gamma-correct for gamma=2.0.
  auto scale = 1.0 / samples_per_pixel;
  r = std::sqrt(scale * r);
  g = std::sqrt(scale * g);
  b = std::sqrt(scale * b);

  // Write the translated [0,255] value of each color component.
  fs << static_cast<int>(256 * std::clamp<Float>(r, 0, 0.999)) << ' '
     << static_cast<int>(256 * std::clamp<Float>(g, 0, 0.999)) << ' '
     << static_cast<int>(256 * std::clamp<Float>(b, 0, 0.999)) << '\n';
}

#endif
