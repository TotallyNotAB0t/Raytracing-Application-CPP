//
// Created by pierr on 26-Apr-23.
//

#include "../include/Point.h"

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::~Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point Point::operator+(const Point &p) const {
    Point res;
    res.x = this->x + p.x;
    res.y = this->y + p.y;
    res.z = this->z + p.z;
    return res;
}

Point Point::operator-(const Point &p) const {
    Point res;
    res.x = this->x - p.x;
    res.y = this->y - p.y;
    res.z = this->z - p.z;
    return res;
}

Point Point::operator*(const Point &p) const {
    Point res;
    res.x = this->x * p.x;
    res.y = this->y * p.y;
    res.z = this->z * p.z;
    return res;
}

Point Point::operator/(const Point &p) const {
    Point res;
    res.x = this->x / p.x;
    res.y = this->y / p.y;
    res.z = this->z / p.z;
    return res;
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "X : " << p.x << ", " << "Y : " << p.y << ", " << "Z : " << p.z << '.' << std::endl;
    return os;
}
