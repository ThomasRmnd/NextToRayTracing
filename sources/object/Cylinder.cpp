#include <cmath>

#include "object/Cylinder.hpp"
#include "ray/Hit.hpp"

InfiniteCylinder::InfiniteCylinder(const Vec3& pos, const Vec3& w, float radius) : 
    HittableObject(pos, w),
    CircularObject(radius)
{};

Hit InfiniteCylinder::intersect(const Ray& ray) const {
    float a = cross(ray.getDir(), m_w).norm2();
    float b = 2.f * (cross(ray.getDir(), m_w) * cross(ray.getOrig() - m_pos, m_w));
    float c = cross(ray.getOrig() - m_pos, m_w).norm2() - m_radius * m_radius;
    float delta = b * b - 4.f * a * c;
    if (delta < 0.f) {
        return Hit(nullptr, Vec3(0.f));
    }
    float t1 = (-b - sqrt(delta)) / (2.f * a);
    float t2 = (-b + sqrt(delta)) / (2.f * a);
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

Cylinder::Cylinder(const Vec3& pos, const Vec3& w, float radius, float height) :
    HittableObject(pos, w),
    m_height(height)
{
    m_disk_top = new Disk(m_pos + m_w * (m_height/2.f), m_w, radius);
    m_disk_bottom = new Disk(m_pos - m_w * (m_height/2.f), m_w, radius);
    m_cylinder = new InfiniteCylinder(m_pos, m_w, radius);
}

Cylinder::~Cylinder() {
    delete m_disk_top;
    delete m_disk_bottom;
    delete m_cylinder;
}

Hit Cylinder::intersect(const Ray& ray) const {
    Hit hit = m_cylinder->intersect(ray);
    if (hit.getObj() != nullptr) {
        if (std::abs((hit.getPos() - m_pos) * m_w ) <= m_height / 2.f) {
            return hit;
        }
    }
    hit = m_disk_top->intersect(ray);
    if (hit.getObj() != nullptr) {
        return hit;
    }
    hit = m_disk_bottom->intersect(ray);
    if (hit.getObj() != nullptr) {
        return hit;
    }
    return Hit(nullptr, Vec3(0.f));
}