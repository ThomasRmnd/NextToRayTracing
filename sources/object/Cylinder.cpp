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
        return Hit();
    }
    float t1 = (-b - sqrt(delta)) / (2.f * a);
    float t2 = (-b + sqrt(delta)) / (2.f * a);
    if (t1 > 1.e-5f) { // Not the same position
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

Vec3 InfiniteCylinder::getNormal(const Vec3& pos) const {
    return (((pos - m_pos) * m_u) * m_u + ((pos - m_pos) * m_v) * m_v).normalize();
}

Cylinder::Cylinder(const Vec3& pos, const Vec3& w, float radius, float height) :
    HittableObject(pos, w),
    m_height(height)
{
    m_disk_top = new Disk(m_pos + m_w * (m_height/2.f), m_w, radius);
    m_disk_bottom = new Disk(m_pos - m_w * (m_height/2.f), -m_w, radius);
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
    Hit top_hit = m_disk_top->intersect(ray);
    Hit bottom_hit = m_disk_bottom->intersect(ray);

    if (top_hit.getObj() != nullptr) {
        if (bottom_hit.getObj() != nullptr) {
            return (top_hit.getDist() < bottom_hit.getDist()) ? top_hit : bottom_hit;
        }
        return top_hit;
    }
    if (bottom_hit.getObj() != nullptr) {
        return bottom_hit;
    }

    return Hit();
}

Vec3 Cylinder::getNormal(const Vec3& pos) const {
    float w_dot_pos = (pos - m_pos) * m_w;
    if (w_dot_pos > m_height / 2.f) {
        return m_disk_top->getNormal(pos);
    }
    else if (w_dot_pos < -m_height / 2.f) {
        return m_disk_bottom->getNormal(pos);
    }
    else {
        return m_cylinder->getNormal(pos);
    }
}