//
// Created by pierr on 21-May-23.
//

#ifndef RTX_SPHEREOBJ_H
#define RTX_SPHEREOBJ_H
#include "InstantiableObject.h"
#include "../../Classes/Coordinates/include/Vector.h"

class SphereObj : public InstantiableObject {
public:
    float radius;
    Vector position;
    SphereObj(float r, const Vector& v);
};

#endif //RTX_SPHEREOBJ_H