#include "Triangle.h"

Triangle::~Triangle()
{
}

Triangle::Triangle(const Point& p)
{
    trans = Matrix();
    translate(p.x, p.y, p.z);
}

Triangle::Triangle(float x, float y, float z)
{
    trans = Matrix();
    translate(x, y, z);
}

bool Triangle::intersect(const Ray& ray, Point& impact) const
{

    return false;
}

Ray Triangle::getNormal(const Point& p, const Point& o) const
{
    Point lp = globalToLocal(p);
    Point lo = globalToLocal(o);

    Vector normal = (Vector(0, 0, 0) - lp).cross(Vector(1, 0, 0) - lp);
    normal = normal.normalized();

    if (normal.dot(lp - Point(0, 0, 0)) < 0)
    {
        normal = -normal;
    }

    return localToGlobal(Ray(lp, normal)).normalized();
}

Point Triangle::getTextureCoordinates(const Point& p) const
{
    Point lp = globalToLocal(p);

    return Point(0, 0, 0);
}