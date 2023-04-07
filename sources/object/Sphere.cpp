#include <iostream>
#include <cmath>

#include "object/Sphere.hpp"

Sphere::Sphere(const Vec3& pos, float radius) : 
    HittableObject(pos), 
    CircularObject(radius) 
{};

Hit Sphere::intersect(const Ray& ray) const {
    float a = ray.getDir().norm2();
    float b = 2.f * (ray.getDir() * (ray.getOrig() - m_pos));
    float c = (ray.getOrig() - m_pos).norm2() - m_radius * m_radius;
    float delta = b * b - 4.f * a * c;
    if (delta < 0.f) {
        return Hit(nullptr, Vec3(0.f));
    }
    float t1 = (-b - std::sqrt(delta)) / (2.f * a);
    float t2 = (-b + std::sqrt(delta)) / (2.f * a);
    if (t1 > 1.e-5f) { // Not the same position
        if (t2 > 1.e-5f) {
            return Hit(this, ray.at(std::min(t1, t2)));
        } 
        else {
            return Hit(this, ray.at(t1));
        }
    }
    if (t2 > 1.e-5f) {
        return Hit(this, ray.at(t2));
    }
    return Hit(nullptr, Vec3(0.f));
}