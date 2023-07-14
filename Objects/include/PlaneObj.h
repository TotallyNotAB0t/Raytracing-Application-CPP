#ifndef RTX_PLANEOBJ_H
#define RTX_PLANEOBJ_H
#include "InstantiableObject.h"
#include "Vector.h"

class PlaneObj : public InstantiableObject 
{
    public:
        int width;
        int height;
        Vector position;
        PlaneObj(int w, int h, const Vector& v);
};


#endif //RTX_PLANEOBJ_H
