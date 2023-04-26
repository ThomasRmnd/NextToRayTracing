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
        return Hit();
    }
    float t1 = (-b - std::sqrt(delta)) / (2.f * a);
    float t2 = (-b + std::sqrt(delta)) / (2.f * a);
    if (t1 > 1.e-5f) { // Not the same position and forward direction
        if (t2 > 1.e-5f) {
            float dist = std::min(t1, t2);
            return Hit(this, dist, ray);
        } 
        else {
            return Hit(this, t1, ray);
        }
    }
    if (t2 > 1.e-5f) {
        return Hit(this, t2, ray);
    }
    return Hit();
}

Vec3 Sphere::getNormal(const Vec3& pos) const {
    return (pos - m_pos).normalize();
}