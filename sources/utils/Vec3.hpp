#pragma once

#include <iostream>

class Vec3 {

private:

    float m_x, m_y, m_z;

public:

    // Constructors

    Vec3();
    Vec3(float x, float y, float z);
    Vec3(const Vec3& other) = default;

    // Destructor

    ~Vec3() = default;

    // Operators

    Vec3& operator=(const Vec3& other) = default;
    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator*=(float value);
    Vec3& operator/=(float value);
    Vec3 operator-() const;

    // Methods

    float x() const;
    float y() const;
    float z() const;
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void set(float x, float y, float z);
    float dot(const Vec3& other) const;
    float norm() const;
    Vec3 normalized() const;
    Vec3& normalize();
    Vec3 cross(const Vec3& other) const;

    // Friend functions

    friend Vec3 operator+(const Vec3& left, const Vec3& right);
    friend Vec3 operator-(const Vec3& left, const Vec3& right);
    friend Vec3 operator*(const Vec3& left, float value);
    friend Vec3 operator*(float value, const Vec3& right);
    friend Vec3 operator/(const Vec3& left, float value);
    friend float norm(const Vec3& vector);
    friend Vec3 normalized(const Vec3& vector);
    friend Vec3& normalize(Vec3& vector);
    friend float dot(const Vec3& left, const Vec3& right);
    friend Vec3 cross(const Vec3& left, const Vec3& right);
    friend std::ostream& operator<<(std::ostream& stream, const Vec3& vector);

};