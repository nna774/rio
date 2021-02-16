#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

template <class T>
class Vec3_impl {
 public:
  Vec3_impl() : e{0, 0, 0} {}
  Vec3_impl(T e0, T e1, T e2) : e{e0, e1, e2} {}

  T x() const { return e[0]; }
  T y() const { return e[1]; }
  T z() const { return e[2]; }

  Vec3_impl operator-() const { return Vec3_impl(-e[0], -e[1], -e[2]); }
  T operator[](int i) const { return e[i]; }
  T &operator[](int i) { return e[i]; }

  Vec3_impl &operator+=(const Vec3_impl &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }
  Vec3_impl &operator*=(const T t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }
  Vec3_impl &operator/=(const T t) { return *this *= 1 / t; }

  T length() const { return std::sqrt(length_squared()); }
  T length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

 public:
  T e[3];
};

template <class T>
inline std::ostream &operator<<(std::ostream &out, const Vec3_impl<T> &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

template <class T>
inline Vec3_impl<T> operator+(const Vec3_impl<T> &u, const Vec3_impl<T> &v) {
  return Vec3_impl<T>(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
template <class T>
inline Vec3_impl<T> operator-(const Vec3_impl<T> &u, const Vec3_impl<T> &v) {
  return Vec3_impl<T>(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
template <class T>
inline Vec3_impl<T> operator*(const Vec3_impl<T> &u, const Vec3_impl<T> &v) {
  return Vec3_impl<T>(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
template <class T>
inline Vec3_impl<T> operator*(double t, const Vec3_impl<T> &v) {
  return Vec3_impl<T>(t * v.e[0], t * v.e[1], t * v.e[2]);
}
template <class T>
inline Vec3_impl<T> operator*(const Vec3_impl<T> &v, double t) {
  return t * v;
}
template <class T>
inline Vec3_impl<T> operator/(Vec3_impl<T> v, double t) {
  return (1 / t) * v;
}

template <class T>
inline double dot(const Vec3_impl<T> &u, const Vec3_impl<T> &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}
template <class T>
inline Vec3_impl<T> cross(const Vec3_impl<T> &u, const Vec3_impl<T> &v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
template <class T>
inline Vec3_impl<T> unit_vector(Vec3_impl<T> v) {
  return v / v.length();
}

using Float = double;
using Vec3 = Vec3_impl<Float>;

// Type aliases for Vec3
using Point3 = Vec3;  // 3D point
using Color = Vec3;   // RGB color

#endif
