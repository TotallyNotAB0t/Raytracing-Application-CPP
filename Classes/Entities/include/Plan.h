#ifndef RTX_PLAN_H
#define RTX_PLAN_H

#include "Object.h"

class Plan : public Object 
{
public:
    Plan() : Object() {};
    Plan(const Point& p);
    Plan(float x, float y, float z);
    Plan(const Material& mat) : Object(mat) {};
    ~Plan();

    bool intersect(const Ray& ray, Point& impact) const override;
    Ray getNormal(const Point &p, const Point &o) const override;
    Point getTextureCoordinates(const Point &p) const override;

};

#endif //RTX_PLAN_H
