#ifndef RTX_POINT_H
#define RTX_POINT_H
#include <iostream>

class Vector;

class Point 
{
    public:
        float x;
        float y;
        float z;
    public:
        Point();
        Point(float x, float y, float z);
        float dot(const Point& p) const;
        float operator[](int val) const;
        float& operator[](int val);
        Point operator+(Point const& p) const;
        Point operator-(Point const& p) const;
        Point operator*(Point const& p) const;
        Point operator/(Point const& p) const;
        Point operator/(float const& f) const;
        Point operator+(const Vector& v) const;
        Point operator-() const;
        float norm() const;
        friend std::ostream& operator<<(std::ostream& os, const Point& p);
        ~Point();
};
#include "Vector.h"

#endif //RTX_POINT_H
