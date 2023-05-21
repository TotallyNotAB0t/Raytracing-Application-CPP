//
// Created by pierr on 20-May-23.
//

#ifndef RTX_PLAN_H
#define RTX_PLAN_H

#include "Object.h"

class Plan : public Object {
    bool intersect(const Ray& ray, Point& impact) const override;
    Ray getNormal(const Point &p, const Point &o) const override;
    Point getTextureCoordinates(const Point &p) const override;

};

#endif //RTX_PLAN_H
