#ifndef RTX_TRIANGLE_H
#define RTX_TRIANGLE_H

#include "Object.h"

class Triangle : public Object
{
private:
    Point a; // First vertex of the triangle
    Point b; // Second vertex of the triangle
    Point c; // Third vertex of the triangle

public:
    Triangle();
    Triangle(const Point &v0, const Point &v1, const Point &v2);
    Triangle(const Triangle& triangle);
    Triangle(const Material& mat) : Object(mat) {};
    ~Triangle();

    bool intersect(const Ray& ray, Point& impact) const override;
    Ray getNormal(const Point& p, const Point& o) const override;
    Point getTextureCoordinates(const Point& p) const override;
};

#endif //RTX_TRIANGLE_H
