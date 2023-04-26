#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <initializer_list>

#include "random/RandomGenerator.h"
#include "utils/Mat.hpp"

template<std::size_t NRows, std::size_t NCols> class Mat;

template<std::size_t N>
class Vec {

private:

    std::vector<float> m_vec;

public:

    // Constructors

    Vec(float value = 0.f) : m_vec(N, value) {};
    Vec(const Vec<N>& left, const Vec<N>& right) {
        *this = left - right;
    }
    template<typename... Args>
    Vec(float first, Args... args) : m_vec{first, args...} {
        if (m_vec.size() != N)
            throw std::out_of_range("Vec::Vec() : m_vec.size() != N");
    }
    Vec(const Vec<N>& other) = default;

    // Destructor

    ~Vec() = default;

    // Operators

    Vec<N>& operator=(const Vec<N>& other) = default;
    Vec<N>& operator=(std::initializer_list<float> list) {
        m_vec = list;
        if (m_vec.size() != N)
            throw std::out_of_range("Vec::operator=() : m_vec.size() != N");
        return *this;
    };
    Vec<N>& operator+=(const Vec<N>& other) {
        for (std::size_t i = 0; i < N; ++i)
            m_vec[i] += other.m_vec[i];
        return *this;
    };
    Vec<N>& operator-=(const Vec<N>& other) {
        for (std::size_t i = 0; i < N; ++i)
            m_vec[i] -= other.m_vec[i];
        return *this;
    };
    Vec<N>& operator*=(float value) {
        for (std::size_t i = 0; i < N; ++i)
            m_vec[i] *= value;
        return *this;
    };
    Vec<N>& operator/=(float value) {
        for (std::size_t i = 0; i < N; ++i)
            m_vec[i] /= value;
        return *this;
    };
    Vec<N> operator-() const {
        Vec<N> result;
        for (std::size_t i = 0; i < N; ++i)
            result.m_vec[i] = -m_vec[i];
        return result;
    };
    float operator[](std::size_t index) const {
        if (index >= N)
            throw std::out_of_range("Vec::operator[]() : index >= N");
        return m_vec[index];
    };
    float& operator[](std::size_t index) {
        if (index >= N)
            throw std::out_of_range("Vec::operator[]() : index >= N");
        return m_vec[index];
    };

    // Methods

    float x() const {
        if (N < 1)
            throw std::out_of_range("Vec::x() : N < 1");
        return m_vec[0];
    };
    float& x() {
        if (N < 1)
            throw std::out_of_range("Vec::x() : N < 1");
        return m_vec[0];
    };
    float y() const {
        if (N < 2)
            throw std::out_of_range("Vec::y() : N < 2");
        return m_vec[1];
    };
    float& y() {
        if (N < 2)
            throw std::out_of_range("Vec::y() : N < 2");
        return m_vec[1];
    };
    float z() const {
        if (N < 3)
            throw std::out_of_range("Vec::z() : N < 3");
        return m_vec[2];
    };
    float& z() {
        if (N < 3)
            throw std::out_of_range("Vec::z() : N < 3");
        return m_vec[2];
    };
    float norm() const {
        return std::sqrt(norm2());
    };
    float norm2() const {
        return ((*this) * (*this));
    };
    Vec normalize() const {
        return *this / norm();
    };
    Vec cross(const Vec& other) const {
        if (N != 3)
            throw std::out_of_range("Vec::cross() : N != 3");
        return Vec(y() * other.z() - z() * other.y(), z() * other.x() - x() * other.z(), x() * other.y() - y() * other.x());
    };
    float cos_angle(const Vec& other) const {
        return ((*this) * other) / (norm() * other.norm());
    };
    float distance(const Vec& other) const {
        return (*this - other).norm();
    };
    std::size_t size() const {
        return N;
    };

    // Static methods

    static Vec<N> zeros() {
        return Vec<N>(0.f);
    };
    static Vec<N> random() {
        UniformGenerator generator;
        return Vec<N>(generator.generate(), generator.generate(), generator.generate());
    }
    static Vec<N> random(float min, float max) {
        UniformGenerator generator;
        return Vec<N>(generator.generate(min, max), generator.generate(min, max), generator.generate(min, max));
    }
    static Vec<N> set_norm_theta_phi(float norm, float theta, float phi) {
        if (N != 3)
            throw std::out_of_range("Vec::set_norm_theta_phi() : N != 3");
        return Vec(norm * std::sin(theta) * std::cos(phi), norm * std::sin(theta) * std::sin(phi), norm * std::cos(theta));
    } 
    static Vec<N> random_unit_ball() {
        UniformGenerator generator;
        float norm = generator.generate(0.f, 1.f);
        float theta = generator.generate(0.f, M_PI);
        float phi = generator.generate(0.f, 2 * M_PI);
        return set_norm_theta_phi(norm, theta, phi);
    }
    static Vec<N> random_unit_sphere() {
        UniformGenerator generator;
        float theta = generator.generate(0.f, M_PI);
        float phi = generator.generate(0.f, 2 * M_PI);
        return set_norm_theta_phi(1.f, theta, phi);
    }

    // Friend functions

    friend Vec<N> operator+(const Vec<N>& left, const Vec<N>& right) {
        return Vec<N>(left) += right;
    }
    friend Vec<N> operator-(const Vec<N>& left, const Vec<N>& right) {
        return Vec<N>(left) -= right;
    }
    friend Vec<N> operator*(const Vec<N>& left, float value) {
        return Vec<N>(left) *= value;
    }
    friend Vec<N> operator*(float value, const Vec<N>& right) {
        return Vec<N>(right) *= value;
    }
    friend float operator*(const Vec<N>& left, const Vec<N>& right) {
        float result = 0.f;
        for (std::size_t i = 0; i < N; i++)
            result += left.m_vec[i] * right.m_vec[i];
        return result;
    }
    template<std::size_t ON>
    friend Vec<ON> operator*(const Vec<N>& left, const Mat<N, ON>& right) {
        Vec<ON> result;
        for (std::size_t j = 0; j < N; j++) {
            for (std::size_t i = 0; i < ON; i++) {
                result[i] += left[j] * right[j][i];
            }
        }
        return result;
    }
    friend Vec<N> operator/(const Vec<N>& left, float value) {
        return Vec<N>(left) /= value;
    }
    friend float norm(const Vec<N>& vector) {
        return vector.norm();
    }
    friend float norm2(const Vec<N>& vector) {
        return vector.norm2();
    }
    friend Vec<N> normalize(const Vec<N>& vector) {
        return vector.normalize();
    }
    friend Vec<N> cross(const Vec<N>& left, const Vec<N>& right) {
        return left.cross(right);
    }
    friend float cos_angle(const Vec<N>& left, const Vec<N>& right) {
        return left.cos_angle(right);
    }
    friend float distance(const Vec<N>& left, const Vec<N>& right) {
        return left.distance(right);
    }
    friend bool operator==(const Vec<N>& left, const Vec<N>& right) {
        return left.m_vec == right.m_vec;
    }
    friend std::ostream& operator<<(std::ostream& stream, const Vec<N>& vector) {
        stream << "(";
        for (size_t i = 0; i < N; ++i) {
            stream << vector.m_vec[i];
            if (i != N - 1)
                stream << ", ";
        }
        stream << ")";
        return stream;
    }

};

typedef Vec<2> Vec2;
typedef Vec<3> Vec3;