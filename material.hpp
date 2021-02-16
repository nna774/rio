#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.hpp"

struct HitRecord;

class Material {
 public:
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       Color& attenuation, Ray& scattered) const = 0;
};

#endif
