#include <omp.h>

#include <iostream>
#include <optional>

#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "utils.hpp"
#include "vec3.hpp"

std::optional<Float> hit_sphere(const Point3& center, Float radius,
                                const Ray& r) {
  Vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto harf_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = harf_b * harf_b - a * c;
  if (discriminant < 0) {
    return std::nullopt;
  }
  return (-harf_b - std::sqrt(discriminant)) / a;
}

Color ray_color(const Ray& r, const Hittable& world, int depth) {
  if (depth <= 0) return Color(0, 0, 0);
  HitRecord rec;
  if (world.hit(r, 0.001, infinity, rec)) {
    Ray scattered;
    Color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth - 1);
    return Color(0, 0, 0);
  }
  Vec3 unit_direction = unit_vector(r.direction());
  auto t2 = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t2) * Color{1.0, 1.0, 1.0} + t2 * Color{0.5, 0.7, 1.0};
}

int main() {
  // Image
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 4000;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  // World
  HittableList world;
  auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
  auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
  auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2));

  world.add(
      std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

  // Camera
  Camera camera;

  // Render
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      Color pixel_color(0, 0, 0);
      std::array<Color, samples_per_pixel> arr;
      // pragma omp parallel for
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_float()) / (image_width - 1);
        auto v = (j + random_float()) / (image_height - 1);
        Ray r = camera.get_ray(u, v);
        arr[s] = ray_color(r, world, max_depth);
      }
      pixel_color = std::accumulate(begin(arr), end(arr), Color{});
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";

  return 0;
}
