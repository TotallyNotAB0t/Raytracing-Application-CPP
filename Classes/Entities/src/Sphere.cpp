#include "Sphere.h"

bool Sphere::intersect(const Ray& ray, Point& impact) const
{
    Ray r = globalToLocal(ray).normalized();
    float a = r.vector.dot(r.vector);
    float b = 2*r.vector.dot(r.origin);
    float c = r.origin.dot(r.origin)-1.0;
    float delta = b*b-4*a*c;

    if (delta < 0) 
    { 
        return false; 
    }

    float t;
    if(delta<0.0001)
    {
        t = -b/(2*a);
    }
    else
    {
        t = (-b-sqrt(delta))/(2*a);
        if(t<0)t = (-b+sqrt(delta))/(2*a);
    }
    if (t < 0)
    {
        return false;
    }

    Point p = r.origin+t*r.vector;
    impact = localToGlobal(p);
    return true;
}

Ray Sphere::getNormal(const Point& p, const Point& o) const
{
    Point lp = globalToLocal(p);
    Point lo = globalToLocal(o);
    if ((lo - Point(0, 0, 0)).norm() < 1) 
    { 
        return localToGlobal(Ray(lp, -lp)).normalized(); 
    }
    return localToGlobal(Ray(lp,lp)).normalized();
}

Point Sphere::getTextureCoordinates(const Point& p) const 
{
    Point lp = globalToLocal(p);
    float rho = std::sqrt(lp.dot(lp));
    float theta = std::atan2(lp[1], lp[0]);
    float sigma = std::acos(lp[2]/rho);
    float x = -theta/(2*M_PI)+0.5;
    float y = sigma/M_PI;
    return Point(x,y,0);
}

Sphere::~Sphere() 
{

}

Sphere::Sphere(const Point& p) 
{
    trans = Matrix();
    translate(p.x, p.y, p.z);
}

Sphere::Sphere(float x, float y, float z)
{
    trans = Matrix();
    translate(x, y, z);
}
