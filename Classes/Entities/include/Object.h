//
// Created by pierr on 21-May-23.
//

#ifndef RTX_OBJECT_H
#define RTX_OBJECT_H

#include "../../include/Entity.h"
#include "../../include/Material.h"

class Object : public Entity {
public:
    virtual Point getTextureCoordinates(const Point& p) const = 0;
    virtual Material getMaterial(const Point& p) const = 0;
    virtual Ray getNormal(const Point& p, const Point& o) const = 0;
    virtual bool intersect(const Ray& ray, Point& impact) const = 0;
};

#endif //RTX_OBJECT_H
