//
// Created by pierr on 19-May-23.
//

#ifndef RTX_HVECTOR_H
#define RTX_HVECTOR_H

#include <iostream>

class HVector {
private:
    float x;
    float y;
    float z;
    float w;

public:
    HVector();
    HVector(float x, float y, float z, float w);
    float getX() const;
    float getY() const;
    float getZ() const;
    float getW() const;
    HVector operator+(const HVector& vector) const;
    HVector operator-(const HVector& vector) const;
    HVector operator*(float scalar) const;
    HVector operator/(float scalar) const;
    float dot(const HVector& vector) const;
    HVector cross(const HVector& vector) const;
    float norm() const;
    HVector normalized() const;
    friend std::ostream& operator<<(std::ostream& os, const HVector& vector);
    ~HVector();
};

#endif // RTX_HVECTOR_H
