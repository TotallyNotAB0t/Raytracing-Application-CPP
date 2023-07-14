#include "Carre.h"

bool Carre::intersect(const Ray &ray, Point &impact) const 
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
    if (p[0] < -1 || p[0]>1 || p[1] < -1 || p[1]>1)
    {
        return false;
    }
    impact = localToGlobal(p);
    return true;
}

