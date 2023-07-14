#ifndef RTX_VECTOR_H
#define RTX_VECTOR_H
#include <cmath>
#include <iostream>

class Point;

class Vector
{
public:
    float x;
    float y;
    float z;
public:
    Vector();
    Vector(float x, float y, float z);
    Vector(const Vector& v);

    Vector& operator=(const Vector& v);
    Vector(Vector&& v) noexcept;
    Vector& operator=(Vector&& v) noexcept;

    float operator[](int val) const;
    float& operator[](int val);

    float norm() const;
    Vector normalized() const;

    float dot(const Vector& v) const;
    float dot(const Point& p) const;

    Vector operator-() const;
    Vector operator+(Vector const& v) const;
    Vector operator-(Vector const& v) const;
    Vector operator*(float val) const;
    friend Vector operator*(float val, const Vector& v);
    Vector operator/(float val) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector& v);

    ~Vector();

    Vector(Point point);

    float vlength() const;
};
#include "Point.h"
#endif //RTX_VECTOR_H
