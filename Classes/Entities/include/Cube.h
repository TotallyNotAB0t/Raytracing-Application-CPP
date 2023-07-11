//
// Created by pierr on 21-May-23.
//

#ifndef RTX_CUBE_H
#define RTX_CUBE_H

#include "Object.h"

class Cube : public Object {
public:
    Cube() : Object(){};
    Cube(const Material& mat) : Object(mat) {};
    ~Cube();
    float interSide(const Ray &r, int dim, float offset) const;
    bool intersect(const Ray &ray, Point &impact) const override;
    Ray getNormal(const Point &p, const Point &o) const override;
    Point getTextureCoordinates(const Point &p) const override;
};

#endif //RTX_CUBE_H
