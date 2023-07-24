#include "Triangle.h"
#include "HRay.h"

bool Triangle::intersect(const Ray& ray, Point& impact) const
{
    HRay r = ray;

    HVector _p0 = trans * HVector(a.x, a.y, a.z, 1.0);
    HVector _p1 = trans * HVector(b.x, b.y, b.z, 1.0);
    HVector _p2 = trans * HVector(c.x, c.y, c.z, 1.0);

    Vector v1(_p1.x - _p0.x, _p1.y - _p0.y, _p1.z - _p0.z);
    Vector v2(_p2.x - _p0.x, _p2.y - _p0.y, _p2.z - _p0.z);

    Vector tmpN = v1.cross(v2);

    HVector N = HVector(tmpN.x, tmpN.y, tmpN.z, 0.0);

    float ND = N.dot(r.vector);
    if (ND == 0.0) {
        return false;
    }

    float d = -N.dot(_p0);
    HVector temp = HVector(r.origin.x, r.origin.y, r.origin.z, r.origin.w);
    float t = -(N.dot(temp) + d) / ND;

    if (t < 0) {
        return false;
    }

    Point tempp = Point(r.origin.x + (r.vector.x * t), r.origin.y + (r.vector.y * t), r.origin.z + (r.vector.z * t));
    impact = tempp;
    HPoint localimpact = HPoint(r.origin.x + (r.vector.x * t), r.origin.y + (r.vector.y * t), r.origin.z + (r.vector.z * t), r.origin.w + (r.vector.w * t));

    Vector p(localimpact.x, localimpact.y, localimpact.z);

    Vector vp0(p.x - _p0.x, p.y - _p0.y, p.z - _p0.z);
    Vector _C = v1.cross(vp0);
    HVector C(_C.x, _C.y, _C.z, 0.0);
    if (N.dot(C) < 0) {
        return false;
    }

    Vector v3(_p2.x - _p1.x, _p2.y - _p1.y, _p2.z - _p1.z);
    Vector vp1(p.x - _p1.x, p.y - _p1.y, p.z - _p1.z);
    _C = v3.cross(vp1);
    C = HVector(_C.x, _C.y, _C.z, 0.0);
    if (N.dot(C) < 0) {
        return false;
    }

    Vector v4(_p0.x - _p2.x, _p0.y - _p2.y, _p0.z - _p2.z);
    Vector vp2(p.x - _p2.x, p.y - _p2.y, p.z - _p2.z);
    _C = v4.cross(vp2);
    C = HVector(_C.x, _C.y, _C.z, 0.0);
    if (N.dot(C) < 0) {
        return false;
    }

    return true;
}

Ray Triangle::getNormal(const Point& p, const Point& o) const
{
    Vector v0v1 = b - a;
    Vector v0v2 = c - a;
    Vector normal = v0v1.cross(v0v2).normalized();
    if (normal.dot(o - a) > 0)
    {
        normal = -normal;
    }
    return Ray(p, normal);
}

Point Triangle::getTextureCoordinates(const Point& p) const
{
    // Not implemented for Triangle class
    return Point(0, 0, 0);
}

Triangle::~Triangle()
{

}

Triangle::Triangle() {
    trans = Matrix(-1, 0, 0, 0,
                   0, -1, 0, 0,
                   0, 0, -1, 0,
                   0, 0, 0, -1);
    transInv = trans.inverse();
    this->a = Point(-1, -1, 0);
    this->b = Point(0, 1, 0);
    this->c = Point(1, -1, 0);
}

Triangle::Triangle(const Point& v0, const Point& v1, const Point& v2)
{
    trans = Matrix(-1, 0, 0, 0,
                   0, -1, 0, 0,
                   0, 0, -1, 0,
                   0, 0, 0, -1);
    transInv = trans.inverse();
    this->a = v0;
    this->b = v1;
    this->c = v2;
}

Triangle::Triangle(const Triangle &triangle) {
    this->trans = triangle.trans;
    this->transInv = triangle.transInv;
    this->material = triangle.material;
    this->a = triangle.a;
    this->b = triangle.b;
    this->c = triangle.c;
}
