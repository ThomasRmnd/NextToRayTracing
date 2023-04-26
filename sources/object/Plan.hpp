#pragma once

#include <array>

#include "object/Object.hpp"

class Plan : public HittableObject {

public:

    Plan(const Vec3& pos, const Vec3& w);

    Hit intersect(const Ray& ray) const override;
    Vec3 getNormal(const Vec3& pos) const override;

};

class Disk : public Plan, public CircularObject {

public:

    Disk(const Vec3& pos, const Vec3& w, float radius);

    Hit intersect(const Ray& ray) const override;

};

class Square : public Plan {

private:

    float m_side;

public:

    Square(const Vec3& pos, const Vec3& u, const Vec3& v, const Vec3& w, float side);

    Hit intersect(const Ray& ray) const override;

};