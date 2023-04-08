#include "object/Object.hpp"

Object::Object() :
    m_pos(0.0f, 0.0f, 0.0f),
    m_u(1.0f, 0.0f, 0.0f),
    m_v(0.0f, 1.0f, 0.0f),
    m_w(0.0f, 0.0f, 1.0f)
{}

Object::Object(const Vec3& pos) :
    m_pos(pos),
    m_u(1.0f, 0.0f, 0.0f),
    m_v(0.0f, 1.0f, 0.0f),
    m_w(0.0f, 0.0f, 1.0f)
{}

HittableObject::HittableObject() :
    Object()
{}

HittableObject::HittableObject(const Vec3& pos) :
    Object(pos)
{}

HittableObject::HittableObject(const Vec3& pos, const Vec3& w) :
    Object(pos)
{
    m_w = w.normalize();
    m_u = Vec3(-m_w.z(), 0.f, m_w.x()).normalize();
    m_v = cross(m_w, m_u);
    if (m_v.y() < 0.f) {
        m_u = -m_u;
        m_v = -m_v;
    }
}

void HittableObject::addProperty(Property* prop) {
    m_props.push_back(prop);
}

CircularObject::CircularObject(float radius) :
    m_radius(radius)
{}

float CircularObject::getRadius() const {
    return m_radius;
}