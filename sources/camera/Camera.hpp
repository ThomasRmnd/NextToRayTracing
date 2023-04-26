#pragma once

#include "object/Object.hpp"
#include "ray/Ray.hpp"

class Camera : public Object {

private:

    unsigned int m_res_x, m_res_y;
    float m_x_width, m_y_width;
    float m_zoom;

public:

    Camera(const Vec3& pos, const Vec3& dir_vue, unsigned int res_x, unsigned int res_y, float x_width, float y_width, float zoom);

    Ray getRay(unsigned int x, unsigned int y) const;
    Ray getRay(float x, float y) const;
    unsigned int getResX() const;
    unsigned int getResY() const;

};