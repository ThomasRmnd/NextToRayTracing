#include "ray/Hit.hpp"

Hit::Hit() : m_obj(nullptr), m_pos(Vec3(0.f)), m_dist(0.f) {}

Hit::Hit(const HittableObject* obj, float dist, const Ray& ray) : 
    m_obj(obj), 
    m_dist(dist),
    m_pos(ray.at(dist)),
    m_normal(obj->getNormal(m_pos))
{
    if (m_normal * ray.getDir() > 0.f) {
        m_normal = -m_normal;
    }
}

const HittableObject* Hit::getObj() const {
    return m_obj;
}

float Hit::getDist() const {
    return m_dist;
}

const Vec3& Hit::getPos() const {
    return m_pos;
}

const Vec3& Hit::getNormal() const {
    return m_normal;
}