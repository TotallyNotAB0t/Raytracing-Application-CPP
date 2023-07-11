//
// Created by pierr on 20-May-23.
//

#ifndef RTX_SPHERE_H
#define RTX_SPHERE_H

#include "Object.h"

class Sphere : public Object {
public:
    Sphere() : Object(){};
    Sphere(const Point& p);
    Sphere(float x, float y, float z);
    Sphere(const Material& mat) : Object(mat) {};
    ~Sphere();

    bool intersect(const Ray& ray, Point& impact) const override;
    Ray getNormal(const Point &p, const Point &o) const override;
    Point getTextureCoordinates(const Point &p) const override;
};

#endif //RTX_SPHERE_H
