#ifndef UTILS_H
#define UTILS_H

#include <numbers>
#include <random>

using Float = double;

const Float infinity = std::numeric_limits<Float>::infinity();
const Float pi = std::numbers::pi_v<Float>;
inline Float degrees_to_radians(Float degrees) { return degrees * pi / 180.0; }

inline Float random_float(Float min = 0, Float max = 1) {
  static std::random_device seed_gen;
  static std::mt19937 engine(seed_gen());
  std::uniform_real_distribution<> dist(min, max);
  return dist(engine);
}

#endif
