#pragma once

#include "utils/Vec.hpp"
#include "object/Object.hpp"
#include "ray/Ray.hpp"

class HittableObject;

class Hit {

private:

    const HittableObject* m_obj;
    float m_dist;
    Vec3 m_pos;
    Vec3 m_normal;

public:

    Hit();
    Hit(const HittableObject* obj, float dist, const Ray& ray);

    const HittableObject* getObj() const;
    float getDist() const;
    const Vec3& getPos() const;
    const Vec3& getNormal() const;

};