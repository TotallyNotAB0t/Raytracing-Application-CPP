//
// Created by pierr on 13-May-23.
//

#ifndef RTX_SPHERE_H
#define RTX_SPHERE_H
#include "InstantiableObject.h"
#include "../../CoordinatesClasses/include/Vector.h"

class Sphere : public InstantiableObject {
    public:
        float radius;
        Vector position;
        Sphere(float r, const Vector& v);
};

#endif //RTX_SPHERE_H
