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
    return Hit(nullptr, Vec3(0.f));
}

Cube::Cube(const Vec3& pos, const Vec3& w, float side) :
    HittableObject(pos, w),
    m_side(side)
{
    m_squares[0] = new Square(m_pos + m_w * m_side / 2.f, m_u, m_v, m_w, m_side);
    m_squares[1] = new Square(m_pos - m_w * m_side / 2.f, -m_u, -m_v, -m_w, m_side);
    m_squares[2] = new Square(m_pos + m_u * m_side / 2.f, m_w, m_v, m_u, m_side);
    m_squares[3] = new Square(m_pos - m_u * m_side / 2.f, -m_w, -m_v, -m_u, m_side);
    m_squares[4] = new Square(m_pos + m_v * m_side / 2.f, m_u, m_w, m_v, m_side);
    m_squares[5] = new Square(m_pos - m_v * m_side / 2.f, -m_u, -m_w, -m_v, m_side);
}

Cube::~Cube() {
    for (Square* square : m_squares) {
        delete square;
    }
}

Hit Cube::intersect(const Ray& ray) const {
    Hit hit(nullptr, Vec3(0.f));
    for (Square* square : m_squares) {
        Hit tmp = square->intersect(ray);
        if (tmp.getObj() != nullptr && (hit.getObj() == nullptr || (tmp.getPos() - ray.getOrig()).norm2() < (hit.getPos() - ray.getOrig()).norm2())) {
            hit = tmp;
        }
    }
    return hit;
}