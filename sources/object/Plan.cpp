#include "object/Plan.hpp"

Plan::Plan(const Vec3& pos, const Vec3& w) : 
    HittableObject(pos, w) 
{}

Hit Plan::intersect(const Ray& ray) const {
    if (ray.getDir() * m_w == 0.f) {
        return Hit(); // Do not handle the case where the ray is contained in the plan
    }
    float t = (m_pos - ray.getOrig()) * m_w / (ray.getDir() * m_w);
    if (t > 1.e-5f) {
        return Hit(this, t, ray);
    }
    return Hit();
}

Vec3 Plan::getNormal(const Vec3& pos) const {
    return m_w;
}

Disk::Disk(const Vec3& pos, const Vec3& w, float radius) :
    Plan(pos, w),
    CircularObject(radius)
{}

Hit Disk::intersect(const Ray& ray) const {
    Hit hit = Plan::intersect(ray);
    if (hit.getObj() != nullptr) {
        if ((hit.getPos() - m_pos).norm2() <= m_radius * m_radius) {
            return hit;
        }
    }
    return Hit();
}

Square::Square(const Vec3& pos, const Vec3& u, const Vec3& v, const Vec3& w, float side) :
    Plan(pos, w),
    m_side(side)
{
    m_pos = pos;
    m_u = u;
    m_v = v;
    m_w = w;
}

Hit Square::intersect(const Ray& ray) const {
    Hit hit = Plan::intersect(ray);
    if (hit.getObj() != nullptr) {
        if (std::abs((hit.getPos() - m_pos) * m_u) <= m_side / 2.f && std::abs((hit.getPos() - m_pos) * m_v) <= m_side / 2.f) {
            return hit;
        }
    }
    return Hit();
}