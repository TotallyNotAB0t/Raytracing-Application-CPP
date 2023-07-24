#ifndef RTX_CYLINDER_H
#define RTX_CYLINDER_H

#include "Object.h"

class Cylinder : public Object
{
public:
    Cylinder() : Object() {};
    Cylinder(const Material& mat) : Object(mat) {};
    Cylinder(const Cylinder& cylinder);
    ~Cylinder();

    Point getTextureCoordinates(const Point& p) const override;
    bool intersect(const Ray &ray, Point &impact) const override;
    Ray getNormal(const Point &p, const Point &o) const override;
};

#endif //RTX_CYLINDER_H
