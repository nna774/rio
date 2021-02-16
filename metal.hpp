#ifndef METAL_H
#define METAL_H

#include "hittable.hpp"
#include "material.hpp"

class Metal : public Material {
 public:
  Metal(const Color& a) : albedo(a) {}

  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       Color& attenuation, Ray& scattered) const override {
    Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

 public:
  Color albedo;
};

#endif
