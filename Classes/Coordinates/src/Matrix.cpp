//
// Created by pierr on 10-May-23.
//

#include "../include/Matrix.h"

Matrix::Matrix() {
    m_data[0] = 1;
    m_data[1] = 0;
    m_data[2] = 0;
    m_data[3] = 0;
    m_data[4] = 0;
    m_data[5] = 1;
    m_data[6] = 0;
    m_data[7] = 0;
    m_data[8] = 0;
    m_data[9] = 0;
    m_data[10] = 1;
    m_data[11] = 0;
    m_data[12] = 0;
    m_data[13] = 0;
    m_data[14] = 0;
    m_data[15] = 1;
}

Matrix::Matrix(float m00, float m01, float m02, float m03,
               float m10, float m11, float m12, float m13,
               float m20, float m21, float m22, float m23,
               float m30, float m31, float m32, float m33) {
    m_data[0] = m00;
    m_data[1] = m01;
    m_data[2] = m02;
    m_data[3] = m03;
    m_data[4] = m10;
    m_data[5] = m11;
    m_data[6] = m12;
    m_data[7] = m13;
    m_data[8] = m20;
    m_data[9] = m21;
    m_data[10] = m22;
    m_data[11] = m23;
    m_data[12] = m30;
    m_data[13] = m31;
    m_data[14] = m32;
    m_data[15] = m33;
}

Matrix::Matrix(const Matrix& other) {
    for (int i = 0; i < 16; i++) {
        m_data[i] = other.m_data[i];
    }
}

Matrix::~Matrix() {}

float Matrix::operator()(int i, int j) const {
    return m_data[i * 4 + j];
}

float& Matrix::operator()(int i, int j) {
    return m_data[i * 4 + j];
}

Matrix Matrix::inverse() const {
    Matrix result;
    float det = m_data[0] * (m_data[5] * m_data[10] - m_data[6] * m_data[9])
                - m_data[1] * (m_data[4] * m_data[10] - m_data[6] * m_data[8])
                + m_data[2] * (m_data[4] * m_data[9] - m_data[5] * m_data[8]);

    if (det == 0.0f) {
        return result;
    }

    float inv_det = 1.0f / det;

    result(0, 0) = (m_data[5] * m_data[10] - m_data[6] * m_data[9]) * inv_det;
    result(0, 1) = (m_data[2] * m_data[9] - m_data[1] * m_data[10]) * inv_det;
    result(0, 2) = (m_data[1] * m_data[6] - m_data[2] * m_data[5]) * inv_det;
    result(0, 3) = 0.0f;

    result(1, 0) = (m_data[6] * m_data[8] - m_data[4] * m_data[10]) * inv_det;
    result(1, 1) = (m_data[0] * m_data[10] - m_data[2] * m_data[8]) * inv_det;
    result(1, 2) = (m_data[2] * m_data[4] - m_data[0] * m_data[6]) * inv_det;
    result(1, 3) = 0.0f;

    result(2, 0) = (m_data[4] * m_data[9] - m_data[5] * m_data[8]) * inv_det;
    result(2, 1) = (m_data[1] * m_data[8] - m_data[0] * m_data[9]) * inv_det;
    result(2, 2) = (m_data[0] * m_data[5] - m_data[1] * m_data[4]) * inv_det;
    result(2, 3) = 0.0f;

    result(3, 0) = -(m_data[3] * result(0, 0) + m_data[7] * result(1, 0) + m_data[11] * result(2, 0));
    result(3, 1) = -(m_data[3] * result(0, 1) + m_data[7] * result(1, 1) + m_data[11] * result(2, 1));
    result(3, 2) = -(m_data[3] * result(0, 2) + m_data[7] * result(1, 2) + m_data[11] * result(2, 2));
    result(3, 3) = 1.0f;

    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result(i, j) = m_data[i * 4] * other(0, j)
                    + m_data[i * 4 + 1] * other(1, j)
                    + m_data[i * 4 + 2] * other(2, j)
                    + m_data[i * 4 + 3] * other(3, j);
        }
    }
    return result;
}

HPoint Matrix::operator*(const HPoint& point) const {
    HPoint result;
    result.x = m_data[0] * point.x + m_data[1] * point.y + m_data[2] * point.z + m_data[3] * point.w;
    result.y = m_data[4] * point.x + m_data[5] * point.y + m_data[6] * point.z + m_data[7] * point.w;
    result.z = m_data[8] * point.x + m_data[9] * point.y + m_data[10] * point.z + m_data[11] * point.w;
    result.w = m_data[12] * point.x + m_data[13] * point.y + m_data[14] * point.z + m_data[15] * point.w;
    return result;
}

HVector Matrix::operator*(const HVector& vector) const {
    HVector result;
    result.x = m_data[0] * vector.x + m_data[1] * vector.y + m_data[2] * vector.z + m_data[3] * vector.w;
    result.y = m_data[4] * vector.x + m_data[5] * vector.y + m_data[6] * vector.z + m_data[7] * vector.w;
    result.z = m_data[8] * vector.x + m_data[9] * vector.y + m_data[10] * vector.z + m_data[11] * vector.w;
    result.w = m_data[12] * vector.x + m_data[13] * vector.y + m_data[14] * vector.z + m_data[15] * vector.w;
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    for (int i = 0; i < 4; ++i) {
        os << "| ";
        for (int j = 0; j < 4; ++j) {
            if (m(i,j) < 0){
                os << m(i, j) << ' ';
            } else {
                os << ' ' << m(i, j) << ' ';
            }
        }
        os << '|' << std::endl;
    }
    os << std::endl;
    return os;
}
