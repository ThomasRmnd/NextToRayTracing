#pragma once

#include <iostream>

#include "utils/Vec.hpp"

class Ray {

private:

    Vec3 m_orig;
    Vec3 m_dir;

public:

    Ray(const Vec3& orig, const Vec3& dir) : m_orig(orig), m_dir(dir) {};

    const Vec3& getOrig() const { return m_orig; };
    const Vec3& getDir() const { return m_dir; };
    Vec3 at(float t) const {
        return (m_orig + t * m_dir); 
    };

};