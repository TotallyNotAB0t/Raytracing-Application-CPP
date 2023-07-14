#ifndef RTX_TRIANGLE_H
#define RTX_TRIANGLE_H

#include "Object.h"

class Triangle : public Object
{
public:
    Triangle() : Object() {};
    Triangle(const Point& p);
    Triangle(float x, float y, float z);
    Triangle(const Material& mat) : Object(mat) {};
    ~Triangle();

    bool intersect(const Ray& ray, Point& impact) const override;
    Ray getNormal(const Point& p, const Point& o) const override;
    Point getTextureCoordinates(const Point& p) const override;
};

#endif //RTX_TRIANGLE_H
