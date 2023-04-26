#pragma once

#include "object/Object.hpp"
#include "object/Plan.hpp"

class Cube : public HittableObject {

private:

    float m_side;
    std::array<Square*, 6> m_squares;

public:

    Cube(const Vec3& pos, const Vec3& w, float side);

    ~Cube();

    Hit intersect(const Ray& ray) const override;
    Vec3 getNormal(const Vec3& pos) const override;

};