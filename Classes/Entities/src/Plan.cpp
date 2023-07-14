#include "Plan.h"

bool Plan::intersect(const Ray& ray, Point& impact) const
{
    Ray lr = globalToLocal(ray).normalized();
    if (lr.vector[2]<0.0001 && lr.vector[2]>-0.0001)
    {
        return false;
    }
    if (lr.vector[2] * lr.origin[2] > 0)
    {
        return false;
    }
    float t = -lr.origin[2]/lr.vector[2];
    Point p = lr.origin+t*lr.vector;
    impact = localToGlobal(p);
    return true;
}

Ray Plan::getNormal(const Point& p, const Point& o) const
{
    Point lp = globalToLocal(p);
    Point lo = globalToLocal(o);
    float z = 1;
    if (lo[2] < 0)
    {
        z = -1;
    }
    return localToGlobal(Ray(lp,Vector(0,0,z))).normalized();
}

Point Plan::getTextureCoordinates(const Point& p) const
{
    Point lp = globalToLocal(p);
    float x = lp[0]-(int)lp[0];
    float y = lp[1]-(int)lp[1];
    if (x < 0)
    {
        x += 1;
    }
    if (y < 0) 
    { 
        y += 1; 
    }

    return Point(x,y,0);
}
