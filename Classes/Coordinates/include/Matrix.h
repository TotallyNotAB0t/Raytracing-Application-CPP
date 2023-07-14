#ifndef RTX_MATRIX_H
#define RTX_MATRIX_H

#include "HPoint.h"
#include "HVector.h"

class Matrix 
{
public:
    Matrix();
    Matrix (float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33);
    Matrix(const Matrix& other);
    ~Matrix();

    float operator()(int i, int j) const;
    float& operator()(int i, int j);

    Matrix inverse() const;

    Matrix operator*(const Matrix& other) const;
    HPoint operator*(const HPoint& point) const;
    HVector operator*(const HVector& vector) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

private:
    float m_data[16];
};

#endif //RTX_MATRIX_H
