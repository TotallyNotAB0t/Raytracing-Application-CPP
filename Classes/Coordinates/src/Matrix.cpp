#include "Matrix.h"

Matrix::Matrix() 
{
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
               float m30, float m31, float m32, float m33) 
{
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

Matrix::Matrix(const Matrix& other) 
{
    for (int i = 0; i < 16; i++) {
        m_data[i] = other.m_data[i];
    }
}

Matrix::~Matrix() {}

float Matrix::operator()(int i, int j) const 
{
    return m_data[i * 4 + j];
}

float& Matrix::operator()(int i, int j) 
{
    return m_data[i * 4 + j];
}

Matrix Matrix::inverse() const 
{
    float inv[16], det;
    int i;

    inv[0] = m_data[5]  * m_data[10] * m_data[15] -
             m_data[5]  * m_data[11] * m_data[14] -
             m_data[9]  * m_data[6]  * m_data[15] +
             m_data[9]  * m_data[7]  * m_data[14] +
             m_data[13] * m_data[6]  * m_data[11] -
             m_data[13] * m_data[7]  * m_data[10];

    inv[4] = -m_data[4]  * m_data[10] * m_data[15] +
             m_data[4]  * m_data[11] * m_data[14] +
             m_data[8]  * m_data[6]  * m_data[15] -
             m_data[8]  * m_data[7]  * m_data[14] -
             m_data[12] * m_data[6]  * m_data[11] +
             m_data[12] * m_data[7]  * m_data[10];

    inv[8] = m_data[4]  * m_data[9] * m_data[15] -
             m_data[4]  * m_data[11] * m_data[13] -
             m_data[8]  * m_data[5] * m_data[15] +
             m_data[8]  * m_data[7] * m_data[13] +
             m_data[12] * m_data[5] * m_data[11] -
             m_data[12] * m_data[7] * m_data[9];

    inv[12] = -m_data[4]  * m_data[9] * m_data[14] +
              m_data[4]  * m_data[10] * m_data[13] +
              m_data[8]  * m_data[5] * m_data[14] -
              m_data[8]  * m_data[6] * m_data[13] -
              m_data[12] * m_data[5] * m_data[10] +
              m_data[12] * m_data[6] * m_data[9];

    inv[1] = -m_data[1]  * m_data[10] * m_data[15] +
             m_data[1]  * m_data[11] * m_data[14] +
             m_data[9]  * m_data[2] * m_data[15] -
             m_data[9]  * m_data[3] * m_data[14] -
             m_data[13] * m_data[2] * m_data[11] +
             m_data[13] * m_data[3] * m_data[10];

    inv[5] = m_data[0]  * m_data[10] * m_data[15] -
             m_data[0]  * m_data[11] * m_data[14] -
             m_data[8]  * m_data[2] * m_data[15] +
             m_data[8]  * m_data[3] * m_data[14] +
             m_data[12] * m_data[2] * m_data[11] -
             m_data[12] * m_data[3] * m_data[10];

    inv[9] = -m_data[0]  * m_data[9] * m_data[15] +
             m_data[0]  * m_data[11] * m_data[13] +
             m_data[8]  * m_data[1] * m_data[15] -
             m_data[8]  * m_data[3] * m_data[13] -
             m_data[12] * m_data[1] * m_data[11] +
             m_data[12] * m_data[3] * m_data[9];

    inv[13] = m_data[0]  * m_data[9] * m_data[14] -
              m_data[0]  * m_data[10] * m_data[13] -
              m_data[8]  * m_data[1] * m_data[14] +
              m_data[8]  * m_data[2] * m_data[13] +
              m_data[12] * m_data[1] * m_data[10] -
              m_data[12] * m_data[2] * m_data[9];

    inv[2] = m_data[1]  * m_data[6] * m_data[15] -
             m_data[1]  * m_data[7] * m_data[14] -
             m_data[5]  * m_data[2] * m_data[15] +
             m_data[5]  * m_data[3] * m_data[14] +
             m_data[13] * m_data[2] * m_data[7] -
             m_data[13] * m_data[3] * m_data[6];

    inv[6] = -m_data[0]  * m_data[6] * m_data[15] +
             m_data[0]  * m_data[7] * m_data[14] +
             m_data[4]  * m_data[2] * m_data[15] -
             m_data[4]  * m_data[3] * m_data[14] -
             m_data[12] * m_data[2] * m_data[7] +
             m_data[12] * m_data[3] * m_data[6];

    inv[10] = m_data[0]  * m_data[5] * m_data[15] -
              m_data[0]  * m_data[7] * m_data[13] -
              m_data[4]  * m_data[1] * m_data[15] +
              m_data[4]  * m_data[3] * m_data[13] +
              m_data[12] * m_data[1] * m_data[7] -
              m_data[12] * m_data[3] * m_data[5];

    inv[14] = -m_data[0]  * m_data[5] * m_data[14] +
              m_data[0]  * m_data[6] * m_data[13] +
              m_data[4]  * m_data[1] * m_data[14] -
              m_data[4]  * m_data[2] * m_data[13] -
              m_data[12] * m_data[1] * m_data[6] +
              m_data[12] * m_data[2] * m_data[5];

    inv[3] = -m_data[1] * m_data[6] * m_data[11] +
             m_data[1] * m_data[7] * m_data[10] +
             m_data[5] * m_data[2] * m_data[11] -
             m_data[5] * m_data[3] * m_data[10] -
             m_data[9] * m_data[2] * m_data[7] +
             m_data[9] * m_data[3] * m_data[6];

    inv[7] = m_data[0] * m_data[6] * m_data[11] -
             m_data[0] * m_data[7] * m_data[10] -
             m_data[4] * m_data[2] * m_data[11] +
             m_data[4] * m_data[3] * m_data[10] +
             m_data[8] * m_data[2] * m_data[7] -
             m_data[8] * m_data[3] * m_data[6];

    inv[11] = -m_data[0] * m_data[5] * m_data[11] +
              m_data[0] * m_data[7] * m_data[9] +
              m_data[4] * m_data[1] * m_data[11] -
              m_data[4] * m_data[3] * m_data[9] -
              m_data[8] * m_data[1] * m_data[7] +
              m_data[8] * m_data[3] * m_data[5];

    inv[15] = m_data[0] * m_data[5] * m_data[10] -
              m_data[0] * m_data[6] * m_data[9] -
              m_data[4] * m_data[1] * m_data[10] +
              m_data[4] * m_data[2] * m_data[9] +
              m_data[8] * m_data[1] * m_data[6] -
              m_data[8] * m_data[2] * m_data[5];

    det = m_data[0] * inv[0] + m_data[1] * inv[4] + m_data[2] * inv[8] + m_data[3] * inv[12];

    if (det == 0)
    {
        throw std::runtime_error("Matrix is not invertible.");
    }

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
    {
        inv[i] = inv[i] * det;
    }

    return Matrix(inv[0], inv[1], inv[2], inv[3],
                  inv[4], inv[5], inv[6], inv[7],
                  inv[8], inv[9], inv[10], inv[11],
                  inv[12], inv[13], inv[14], inv[15]);

}

Matrix Matrix::operator*(const Matrix& other) const 
{
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

HPoint Matrix::operator*(const HPoint& point) const 
{
    HPoint result;
    result.x = m_data[0] * point.x + m_data[1] * point.y + m_data[2] * point.z + m_data[3] * point.w;
    result.y = m_data[4] * point.x + m_data[5] * point.y + m_data[6] * point.z + m_data[7] * point.w;
    result.z = m_data[8] * point.x + m_data[9] * point.y + m_data[10] * point.z + m_data[11] * point.w;
    result.w = m_data[12] * point.x + m_data[13] * point.y + m_data[14] * point.z + m_data[15] * point.w;
    return result;
}

HVector Matrix::operator*(const HVector& vector) const 
{
    HVector result;
    result.x = m_data[0] * vector.x + m_data[1] * vector.y + m_data[2] * vector.z + m_data[3] * vector.w;
    result.y = m_data[4] * vector.x + m_data[5] * vector.y + m_data[6] * vector.z + m_data[7] * vector.w;
    result.z = m_data[8] * vector.x + m_data[9] * vector.y + m_data[10] * vector.z + m_data[11] * vector.w;
    result.w = m_data[12] * vector.x + m_data[13] * vector.y + m_data[14] * vector.z + m_data[15] * vector.w;
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) 
{
    for (int i = 0; i < 4; ++i) 
    {
        os << "| ";
        for (int j = 0; j < 4; ++j) 
        {
            float var = m(i,j);
            if (var >= 0) 
            {
                os << ' ';
            }
            if(var == (int)var)
            {
                os << "  ";
            }
            os << var << ' ';
        }
        os << '|' << std::endl;
    }
    os << std::endl;
    return os;
}
