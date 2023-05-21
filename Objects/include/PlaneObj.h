//
// Created by pierr on 13-May-23.
//

#ifndef RTX_PLANEOBJ_H
#define RTX_PLANEOBJ_H
#include "InstantiableObject.h"
#include "../../Classes/Coordinates/include/Vector.h"

class PlaneObj : public InstantiableObject {
    public:
        int width;
        int height;
        Vector position;
        PlaneObj(int w, int h, const Vector& v);
};


#endif //RTX_PLANEOBJ_H
