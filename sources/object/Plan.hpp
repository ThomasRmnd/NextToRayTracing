#pragma once

#include "object/Object.hpp"

class Plan : public HittableObject {

public:

    Plan(const Vec3& pos, const Vec3& w);

    Hit intersect(const Ray& ray) const override;

};

class Disk : public Plan, public CircularObject {

public:

    Disk(const Vec3& pos, const Vec3& w, float radius);

    Hit intersect(const Ray& ray) const override;

};