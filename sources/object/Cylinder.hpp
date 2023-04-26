#pragma once

#include "object/Object.hpp"
#include "object/Plan.hpp"

class InfiniteCylinder : public HittableObject, public CircularObject {

public:

    InfiniteCylinder(const Vec3& pos, const Vec3& w, float radius);

    Hit intersect(const Ray& ray) const override;
    Vec3 getNormal(const Vec3& pos) const override;

};

class Cylinder : public HittableObject {

private:

    Disk* m_disk_top;
    Disk* m_disk_bottom;
    InfiniteCylinder* m_cylinder;
    float m_height;

public:

    Cylinder(const Vec3& pos, const Vec3& w, float radius, float height);

    ~Cylinder();

    Hit intersect(const Ray& ray) const override;
    Vec3 getNormal(const Vec3& pos) const override;

};