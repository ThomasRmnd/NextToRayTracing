#pragma once

#include "utils/Vec.hpp"
#include "ray/Ray.hpp"
#include "ray/Hit.hpp"
#include "object/property/Property.hpp"

class Hit;

class Object {

protected:

    Vec3 m_pos;
    Vec3 m_u;
    Vec3 m_v;
    Vec3 m_w;

public:

    Object();
    Object(const Vec3& pos);

    virtual ~Object() = default;

};

class HittableObject : public Object {

protected:

    std::vector<Property*> m_props;

public:

    HittableObject();
    HittableObject(const Vec3& pos);
    HittableObject(const Vec3& pos, const Vec3& w);

    virtual ~HittableObject() = default;

    void addProperty(Property* prop);
    virtual Hit intersect(const Ray& ray) const = 0;
    virtual Vec3 getNormal(const Vec3& pos) const = 0;

};

class CircularObject {

protected:

    float m_radius;

public:

    CircularObject(float radius);

    float getRadius() const;

};