#include "object/Plan.hpp"

Plan::Plan(const Vec3& pos, const Vec3& w) : 
    HittableObject(pos, w) 
{}

Hit Plan::intersect(const Ray& ray) const {
    if (ray.getDir() * m_w == 0.f) {
        return Hit(nullptr, Vec3(0.f)); // Do not handle the case where the ray is contained in the plan
    }
    float t = (m_pos - ray.getOrig()) * m_w / (ray.getDir() * m_w);
    if (t > 1.e-5f) {
        return Hit(this, ray.at(t));
    }
    return Hit(nullptr, Vec3(0.f));
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
    return Hit(nullptr, Vec3(0.f));
};