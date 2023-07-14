#include "Point.h"

Point::Point() 
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(float x, float y, float z) 
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::~Point() 
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

float Point::dot(const Point& p) const 
{
    return x *p.x + y * p.y + z * p.z;
}

float Point::operator[](int val) const 
{
    switch (val) 
    {
        case 0:
            return this->x;
        case 1:
            return this->y;
        case 2:
            return this->z;
        default:
            throw std::out_of_range("Vector index out of range.");
    }
}

float &Point::operator[](int val) 
{
    switch (val) 
    {
        case 0:
            return this->x;
        case 1:
            return this->y;
        case 2:
            return this->z;
        default:
            throw std::out_of_range("Vector index out of range.");
    }
}

Point Point::operator+(const Point &p) const 
{
    Point res;
    res.x = this->x + p.x;
    res.y = this->y + p.y;
    res.z = this->z + p.z;
    return res;
}

Point Point::operator-(const Point &p) const 
{
    Point res;
    res.x = this->x - p.x;
    res.y = this->y - p.y;
    res.z = this->z - p.z;
    return res;
}

Point Point::operator*(const Point &p) const 
{
    Point res;
    res.x = this->x * p.x;
    res.y = this->y * p.y;
    res.z = this->z * p.z;
    return res;
}

Point Point::operator/(const Point &p) const 
{
    Point res;
    res.x = this->x / p.x;
    res.y = this->y / p.y;
    res.z = this->z / p.z;
    return res;
}

Point Point::operator/(float const& f) const 
{
    return Point(x / f, y / f, z / f);
}

Point Point::operator+(const Vector& v) const 
{
    return Point(x + v.x, y + v.y, z + v.z);
}

Point Point::operator-() const 
{
    return Point(-this->x, -this->y, -this->z);
}

float Point::norm() 
{
    return sqrt(x*x + y*y + z*z);
}

std::ostream &operator<<(std::ostream &os, const Point &p) 
{
    os << "X : " << p.x << ", " << "Y : " << p.y << ", " << "Z : " << p.z << '.' << std::endl;
    return os;
}
