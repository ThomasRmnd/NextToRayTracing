#pragma once

#include "utils/Vec.hpp"
#include "object/Object.hpp"

class HittableObject;

class Hit {

private:

    const HittableObject* m_obj;
    Vec3 m_pos;

public:

    Hit(const HittableObject* obj, const Vec3& pos) : m_obj(obj), m_pos(pos) {};

    const HittableObject* getObj() const { return m_obj; };
    const Vec3& getPos() const { return m_pos; };

};