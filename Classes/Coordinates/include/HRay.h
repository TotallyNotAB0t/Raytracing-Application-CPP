//
// Created by pierr on 20-May-23.
//

#ifndef RTX_HRAY_H
#define RTX_HRAY_H

#include "HPoint.h"
#include "HVector.h"
#include "Ray.h"

class HRay {
public:
    HPoint origin;
    HVector vector;

public:
    HRay();
    HRay(const Ray& r);
    HRay(float ox, float oy, float oz, float vx, float vy, float vz);
    HRay(const HPoint& o, const HVector& v);
    HRay(const HRay& r);

    HRay& operator=(const HRay& r);
    HRay(HRay&& r) noexcept;
    HRay& operator=(HRay&& r) noexcept;

    ~HRay();
};

#endif // RTX_HRAY_H
