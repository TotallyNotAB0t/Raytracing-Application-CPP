#ifndef RTX_HPOINT_H
#define RTX_HPOINT_H

#include "Point.h"

class HPoint 
{

public:
    float x;
    float y;
    float z;
    float w;
public:
    HPoint();
    HPoint(float x, float y, float z, float w);
    HPoint(const HPoint& point, float w);
    HPoint(const Point& point);
    HPoint operator+(const HPoint& point) const;
    HPoint operator-(const HPoint& point) const;
    HPoint operator*(float scalar) const;
    HPoint operator/(float scalar) const;
    friend std::ostream& operator<<(std::ostream& os, const HPoint& point);
    ~HPoint();
};

#endif // RTX_HPOINT_H

