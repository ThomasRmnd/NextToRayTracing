#include <cmath>

#include "utils/Vec3.hpp"

// Constructors

Vec3::Vec3() : m_x(0), m_y(0), m_z(0) {}

Vec3::Vec3(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}

// Operators

Vec3& Vec3::operator+=(const Vec3& other) {
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other) {
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    return *this;
}

Vec3& Vec3::operator*=(float value) {
    m_x *= value;
    m_y *= value;
    m_z *= value;
    return *this;
}

Vec3& Vec3::operator/=(float value) {
    m_x /= value;
    m_y /= value;
    m_z /= value;
    return *this;
}

Vec3 Vec3::operator-() const {
    return Vec3(-m_x, -m_y, -m_z);
}

// Methods

float Vec3::x() const {
    return m_x;
}

float Vec3::y() const {
    return m_y;
}

float Vec3::z() const {
    return m_z;
}

void Vec3::setX(float x) {
    m_x = x;
}

void Vec3::setY(float y) {
    m_y = y;
}

void Vec3::setZ(float z) {
    m_z = z;
}

void Vec3::set(float x, float y, float z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

float Vec3::dot(const Vec3& other) const {
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

float Vec3::norm() const {
    return std::sqrt(dot(*this));
}

Vec3 Vec3::normalized() const {
    return *this / norm();
}

Vec3& Vec3::normalize() {
    return (*this /= norm());
}

Vec3 Vec3::cross(const Vec3& other) const {
    return Vec3(m_y * other.m_z - m_z * other.m_y,
                m_z * other.m_x - m_x * other.m_z,
                m_x * other.m_y - m_y * other.m_x);
}

// Friend functions

Vec3 operator+(const Vec3& left, const Vec3& right) {
    return Vec3(left) += right;
}

Vec3 operator-(const Vec3& left, const Vec3& right) {
    return Vec3(left) -= right;
}

Vec3 operator*(const Vec3& left, float value) {
    return Vec3(left) *= value;
}

Vec3 operator*(float value, const Vec3& right) {
    return Vec3(right) *= value;
}

Vec3 operator/(const Vec3& left, float value) {
    return Vec3(left) /= value;
}

float norm(const Vec3& vector) {
    return vector.norm();
}

Vec3 normalized(const Vec3& vector) {
    return vector.normalized();
}

Vec3& normalize(Vec3& vector) {
    return vector.normalize();
}

float dot(const Vec3& left, const Vec3& right) {
    return left.dot(right);
}

Vec3 cross(const Vec3& left, const Vec3& right) {
    return left.cross(right);
}

std::ostream& operator<<(std::ostream& stream, const Vec3& vector) {
    stream << "(" << vector.x() << ", " << vector.y() << ", " << vector.z() << ")";
    return stream;
}