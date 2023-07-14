#ifndef RTX_CYLINDER_H
#define RTX_CYLINDER_H

#include "Object.h"

class Cylinder : public Object 
{
    bool intersect(const Ray &ray, Point &impact) const override;
    Ray getNormal(const Point &p, const Point &o) const override;
};

#endif //RTX_CYLINDER_H
