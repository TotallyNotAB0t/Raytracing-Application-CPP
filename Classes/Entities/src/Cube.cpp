#include "Cube.h"

float Cube::interSide(const Ray& r, int dim, float offset) const
{
    float t = -1;
    if (r.vector[dim]<0.00001 && r.vector[dim]>-0.00001)
    {
        return -1;
    }
    t = (offset-r.origin[dim])/r.vector[dim];
    if (t < 0)
    {
        return -1;
    }
    for(int d = 0; d < 3; d++)
    {
        if (d == dim)
        {
            continue;
        }
        float x = r.origin[d]+t*r.vector[d];
        if (x < -1 || x > 1)
        {
            return -1;
        }
    }
    return t;
}

bool Cube::intersect(const Ray& ray, Point& impact) const
{
    Ray r = globalToLocal(ray);

    bool result =false;
    float localF;
    float b = 1.f;

    for(int i =0;i < 6;i++)
    {
        if (i == 3)
        {
            b = -b;
        }
        int j = i%3;
        float t = (b-r.origin[j])/r.vector[j];
        Point localimpact = r.origin + t*r.vector;
        impact = localToGlobal( r.origin + t*r.vector);
        if(t > 0)
        {
            if (localimpact[(j-1)<0?2:(j-1)] >= -1 && localimpact[(j-1)<0?2:(j-1)] <= 1 && localimpact[(j+1)%3] >= -1 && localimpact[(j+1)%3] <= 1 )
            {
                result = true;
                localF =t;
            }
        }
    }

    if (!result)
    {
        return false;
    }
    impact = localToGlobal( r.origin + localF*r.vector);

    return true;
}

Ray Cube::getNormal(const Point& p,const Point& o) const
{
    Point lp = globalToLocal(p);
    Point lo = globalToLocal(o);
    Vector v(0,0,0);
    if (lp[0] > 0.999)
    {
        v[0] = 1.0;
    }
    else if (lp[0] < -0.999) { v[0] = -1.0; }
    else if (lp[1] > 0.999) { v[1] = 1.0; }
    else if (lp[1] < -0.999) { v[1] = -1.0; }
    else if (lp[2] > 0.999) { v[2] = 1.0; }
    else if (lp[2] < -0.999) { v[2] = -1.0; }
    if (lo[0]<1 && lo[0]>-1 && lo[1]<1 && lo[1]>-1 && lo[2]<1 && lo[2]>-1)
    {
        return localToGlobal(Ray(lp, -v)).normalized();
    }
    return localToGlobal(Ray(lp,v)).normalized();
}

Point Cube::getTextureCoordinates(const Point& p) const
{
    Point lp = globalToLocal(p);
    if (lp[0] > 0.999 || lp[0] < -0.999) { return Point(lp[2] / 2 + 0.5, lp[1] / 2 + 0.5, 0); }
    if (lp[1] > 0.999 || lp[1] < -0.999) { return Point(lp[0] / 2 + 0.5, lp[2] / 2 + 0.5, 0); }
    if (lp[2] > 0.999 || lp[2] < -0.999) { return Point(lp[0] / 2 + 0.5, lp[1] / 2 + 0.5, 0); }
    return Point(0,0,0);
}

Cube::~Cube() 
{

}
