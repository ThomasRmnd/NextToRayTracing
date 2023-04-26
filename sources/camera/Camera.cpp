#include "camera/Camera.hpp"

Camera::Camera(const Vec3& pos, const Vec3& dir_vue, unsigned int res_x, unsigned int res_y, float x_width, float y_width, float zoom) : 
    m_res_x(res_x), 
    m_res_y(res_y), 
    m_x_width(x_width), 
    m_y_width(y_width), 
    m_zoom(zoom) 
{
    m_pos = pos;
    m_w = normalize(-dir_vue);
    m_u = Vec3(-m_w.z(), 0.f, m_w.x()).normalize();
    m_v = cross(m_w, m_u);
    if (m_v.y() < 0) {
        m_u = -m_u;
        m_v = -m_v;
    }
}

Ray Camera::getRay(unsigned int i, unsigned int j) const {
    float x_ratio = (float)i / (float)m_res_x;
    float y_ratio = (float)j / (float)m_res_y;
    float x = -m_x_width/2.f + x_ratio * m_x_width;
    float y = -m_y_width/2.f + y_ratio * m_y_width;
    float z = -m_zoom;
    Vec3 point = m_pos + x * m_u + y * m_v + z * m_w;
    return Ray(m_pos, point - m_pos);
}

Ray Camera::getRay(float i, float j) const {
    float x_ratio = i / (float)m_res_x;
    float y_ratio = j / (float)m_res_y;
    float x = -m_x_width/2.f + x_ratio * m_x_width;
    float y = -m_y_width/2.f + y_ratio * m_y_width;
    float z = -m_zoom;
    Vec3 point = m_pos + x * m_u + y * m_v + z * m_w;
    return Ray(m_pos, point - m_pos);
}

unsigned int Camera::getResX() const {
    return m_res_x;
}

unsigned int Camera::getResY() const {
    return m_res_y;
}