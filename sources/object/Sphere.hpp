#pragma once

#include "object/Object.hpp"

class Sphere : public HittableObject, public CircularObject {

public:

    Sphere(const Vec3& pos, float radius);

    Hit intersect(const Ray& ray) const override;
    Vec3 getNormal(const Vec3& pos) const override;

};