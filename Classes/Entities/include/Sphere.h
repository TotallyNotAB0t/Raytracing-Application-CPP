//
// Created by pierr on 20-May-23.
//

#ifndef RTX_SPHERE_H
#define RTX_SPHERE_H

#include "Object.h"

class Sphere : public Object {

private:
    Material material;
public:
    Sphere();
    Sphere(const Point& p);
    Sphere(float x, float y, float z);
    Sphere(const Material& mat);
    ~Sphere();

    bool intersect(const Ray& ray, Point& impact) const override;
    Ray getNormal(const Point &p, const Point &o) const override;
    Point getTextureCoordinates(const Point &p) const override;
    Material getMaterial(const Point &p) const override;
};

#endif //RTX_SPHERE_H
