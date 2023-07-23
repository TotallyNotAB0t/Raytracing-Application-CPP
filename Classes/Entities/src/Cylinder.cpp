#include "Cylinder.h"

bool Cylinder::intersect(const Ray& ray, Point& impact) const
{
    Ray r = globalToLocal(ray).normalized();

    float a = r.vector[0]*r.vector[0]+r.vector[2]*r.vector[2];
    float b = 2*(r.vector[0]*r.origin[0]+r.vector[2]*r.origin[2]);
    float c = r.origin[0]*r.origin[0]+r.origin[2]*r.origin[2]-1.0;
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

Ray Cylinder::getNormal(const Point& p, const Point& o) const
{
    Point lp = globalToLocal(p);
    Point lo = globalToLocal(o);
    if ((lo - Point(0, lo[1], 0)).norm() > 1)
    {
        return localToGlobal(Ray(lp, Vector(lp[0], 0, lp[2]))).normalized();
    }
    return localToGlobal(Ray(lp,Vector(-lp[0],0,-lp[2]))).normalized();
}

Point Cylinder::getTextureCoordinates(const Point &p) const {
    return Point();
}

Cylinder::~Cylinder() {

}

Cylinder::Cylinder(const Cylinder &cylinder) {
    this->trans = cylinder.trans;
    this->transInv = cylinder.transInv;
    this->material = cylinder.material;

}
