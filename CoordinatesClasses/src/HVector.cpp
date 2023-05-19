//
// Created by pierr on 19-May-23.
//

#include <cmath>
#include "../include/HVector.h"

HVector::HVector() : x(0), y(0), z(0), w(1) {}

HVector::HVector(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

float HVector::getX() const {
    return x;
}

float HVector::getY() const {
    return y;
}

float HVector::getZ() const {
    return z;
}

float HVector::getW() const {
    return w;
}

HVector HVector::operator+(const HVector& vector) const {
    return HVector(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

HVector HVector::operator-(const HVector& vector) const {
    return HVector(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

HVector HVector::operator*(float scalar) const {
    return HVector(x * scalar, y * scalar, z * scalar, w * scalar);
}

HVector HVector::operator/(float scalar) const {
    return HVector(x / scalar, y / scalar, z / scalar, w / scalar);
}

float HVector::dot(const HVector& vector) const {
    return (x * vector.x) + (y * vector.y) + (z * vector.z) + (w * vector.w);
}

HVector HVector::cross(const HVector& vector) const {
    float crossX = (y * vector.z) - (z * vector.y);
    float crossY = (z * vector.x) - (x * vector.z);
    float crossZ = (x * vector.y) - (y * vector.x);
    return HVector(crossX, crossY, crossZ, 0);
}

float HVector::norm() const {
    return std::sqrt(x * x + y * y + z * z);
}

HVector HVector::normalized() const {
    float magnitude = norm();
    return (*this) / magnitude;
}

std::ostream& operator<<(std::ostream& os, const HVector& vector) {
    os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
    return os;
}

HVector::~HVector() {}
