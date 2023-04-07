#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

#include "utils/Vec.hpp"

template<std::size_t N> class Vec;

template<std::size_t NRows, std::size_t NCols>
class Mat {

private:

    std::vector<Vec<NCols>> m_mat;

public:

    // Constructors

    Mat(float value = 0.f) : m_mat(NRows, Vec<NCols>(value)) {};
    Mat(const Mat<NRows, NCols>& other) = default;

    // Destructor

    ~Mat() = default;

    // Operators

    Mat<NRows, NCols>& operator=(const Mat<NRows, NCols>& other) = default;
    Mat<NRows, NCols>& operator+=(const Mat<NRows, NCols>& other) {
        std::transform(m_mat.begin(), m_mat.end(), other.m_mat.begin(), m_mat.begin(), std::plus<Vec<NCols>>());
        return *this;
    };
    Mat<NRows, NCols>& operator-=(const Mat<NRows, NCols>& other) {
        std::transform(m_mat.begin(), m_mat.end(), other.m_mat.begin(), m_mat.begin(), std::minus<Vec<NCols>>());
        return *this;
    };
    Mat<NRows, NCols>& operator*=(float value) {
        std::for_each(m_mat.begin(), m_mat.end(), std::bind(std::multiplies<Vec<NCols>>(), std::placeholders::_1, value));
        return *this;
    };
    Mat<NRows, NCols>& operator/=(float value) {
        std::for_each(m_mat.begin(), m_mat.end(), std::bind(std::divides<Vec<NCols>>(), std::placeholders::_1, value));
        return *this;
    };
    Mat<NRows, NCols>& operator-() const {
        Mat<NRows, NCols> result;
        std::transform(m_mat.begin(), m_mat.end(), result.m_mat.begin(), std::negate<Vec<NCols>>());
        return result;
    };
    const Vec<NCols>& operator[](std::size_t index) const {
        return m_mat[index];
    };
    Vec<NCols>& operator[](std::size_t index) {
        return m_mat[index];
    };

    // Methods

    Mat<NRows, NCols> transpose() const {
        Mat<NCols, NRows> result;
        for (std::size_t i = 0; i < NRows; ++i) {
            for (std::size_t j = 0; j < NCols; ++j) {
                result[j][i] = m_mat[i][j];
            }
        }
        return result;
    };

    // Friend functions

    friend Mat<NRows, NCols> operator+(const Mat<NRows, NCols>& lhs, const Mat<NRows, NCols>& rhs) {
        return Mat<NRows, NCols>(lhs) += rhs;
    };
    friend Mat<NRows, NCols> operator-(const Mat<NRows, NCols>& lhs, const Mat<NRows, NCols>& rhs) {
        return Mat<NRows, NCols>(lhs) -= rhs;
    };
    friend Mat<NRows, NCols> operator*(const Mat<NRows, NCols>& lhs, float rhs) {
        return Mat<NRows, NCols>(lhs) *= rhs;
    };
    friend Mat<NRows, NCols> operator*(float lhs, const Mat<NRows, NCols>& rhs) {
        return Mat<NRows, NCols>(rhs) *= lhs;
    };
    template<std::size_t ONCols>
    friend Mat<NRows, ONCols> operator*(const Mat<NRows, NCols>& lhs, const Mat<NCols, ONCols>& rhs) {
        Mat<NRows, ONCols> result;
        for (std::size_t i = 0; i < NRows; i++) {
            result = lhs[i] * rhs;
        }
        return result;
    };
    friend Vec<NRows> operator*(const Mat<NRows, NCols>& lhs, const Vec<NCols>& rhs) {
        Vec<NRows> result;
        for (std::size_t i = 0; i < NRows; i++) {
            result[i] = lhs[i] * rhs;
        }
        return result;
    };
    friend Mat<NRows, NCols> operator/(const Mat<NRows, NCols>& lhs, float rhs) {
        return Mat<NRows, NCols>(lhs) /= rhs;
    };
    friend Mat<NCols, NRows> transpose(const Mat<NRows, NCols>& mat) {
        return mat.transpose();
    };
    friend std::ostream& operator<<(std::ostream& os, const Mat<NRows, NCols>& mat) {
        for (const Vec<NCols>& vec : mat.m_mat) {
            os << vec << std::endl;
        }
        return os;
    };

};

typedef Mat<2, 2> Mat2;
typedef Mat<3, 3> Mat3;
typedef Mat<4, 4> Mat4;