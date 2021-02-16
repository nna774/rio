#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"

struct HitRecord {
  Point3 p;
  Vec3 normal;
  Float t;
  bool front_face;

  inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
 public:
  virtual bool hit(const Ray& r, Float t_min, Float t_max,
                   HitRecord& rec) const = 0;
};

#endif
