//
// Created by pierr on 19-May-23.
//

#include "../include/HPoint.h"

HPoint::HPoint() : x(0), y(0), z(0), w(1) {}

HPoint::HPoint(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

HPoint::HPoint(const HPoint& point, float w) : x(point.x), y(point.y), z(point.z), w(w) {}

HPoint HPoint::operator+(const HPoint& point) const {
    return HPoint(x + point.x, y + point.y, z + point.z, w + point.w);
}

HPoint HPoint::operator-(const HPoint& point) const {
    return HPoint(x - point.x, y - point.y, z - point.z, w - point.w);
}

HPoint HPoint::operator*(float scalar) const {
    return HPoint(x * scalar, y * scalar, z * scalar, w * scalar);
}

HPoint HPoint::operator/(float scalar) const {
    return HPoint(x / scalar, y / scalar, z / scalar, w / scalar);
}

std::ostream& operator<<(std::ostream& os, const HPoint& point) {
    os << "(" << point.x << ", " << point.y << ", " << point.z << ", " << point.w << ")";
    return os;
}

HPoint::~HPoint() {}

float HPoint::getX() const {
    return x;
}

float HPoint::getY() const {
    return y;
}

float HPoint::getZ() const {
    return z;
}

float HPoint::getW() const {
    return w;
}
