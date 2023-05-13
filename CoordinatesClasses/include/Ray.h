//
// Created by pierr on 10-May-23.
//

#ifndef RTX_RAY_H
#define RTX_RAY_H

#include "Point.h"
#include "Vector.h"

class Ray {
    private:
        Point origin;
        Vector vector;
    public:
        Ray();
        Ray(float ox, float oy, float oz, float vx, float vy, float vz);
        Ray(const Point& o, const Vector& v);
        Ray(const Ray& r);

        Ray& operator=(const Ray& r);
        Ray(Ray&& r) noexcept;
        Ray& operator=(Ray&& r) noexcept;

        ~Ray();

};

#endif //RTX_RAY_H
