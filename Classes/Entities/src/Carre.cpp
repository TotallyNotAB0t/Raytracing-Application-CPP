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

Ray Carre::getNormal(const Point& p, const Point& o) const {
    Point lp = globalToLocal(p);
    Point lo = globalToLocal(o);

    Vector v1(1, 0, 0);  // First vector on the square's plane
    Vector v2(0, 1, 0);  // Second vector on the square's plane

    Vector normal = v1.cross(v2).normalized();  // Calculate the normal using cross product

    if (lo[0] < 1 && lo[0] > -1 && lo[1] < 1 && lo[1] > -1) {
        return localToGlobal(Ray(lp, -normal)).normalized();
    }
    return localToGlobal(Ray(lp, normal)).normalized();
}

Point Carre::getTextureCoordinates(const Point& p) const {
    Point lp = globalToLocal(p);
    if (lp[0] > 0.999 || lp[0] < -0.999) { return Point(lp[1] / 2 + 0.5, 0, lp[1] / 2 + 0.5); }
    if (lp[1] > 0.999 || lp[1] < -0.999) { return Point(lp[0] / 2 + 0.5, 0, lp[0] / 2 + 0.5); }
    return Point(0, 0, 0);
}

Carre::~Carre()
{

}

Carre::Carre(const Carre &carre) {
    this->trans = carre.trans;
    this->transInv = carre.transInv;
    this->material = carre.material;
}
