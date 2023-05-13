//
// Created by pierr on 13-May-23.
//

#ifndef RTX_PLANE_H
#define RTX_PLANE_H
#include "InstantiableObject.h"
#include "../../CoordinatesClasses/include/Vector.h"

class Plane : public InstantiableObject {
    public:
        int width;
        int height;
        Vector position;
        Plane(int w, int h, const Vector& v);
};


#endif //RTX_PLANE_H
