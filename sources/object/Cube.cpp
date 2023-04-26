#include "object/Cube.hpp"

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
    Hit hit;
    for (Square* square : m_squares) {
        Hit tmp = square->intersect(ray);
        if (tmp.getObj() != nullptr && (hit.getObj() == nullptr || (tmp.getPos() - ray.getOrig()).norm2() < (hit.getPos() - ray.getOrig()).norm2())) {
            hit = tmp;
        }
    }
    return hit;
}

Vec3 Cube::getNormal(const Vec3& pos) const {
    for (Square* square : m_squares) {
        if (square->intersect(Ray(pos, square->getNormal(pos))).getObj() != nullptr) {
            return square->getNormal(pos);
        }
    }
    return Vec3(0.f);
}