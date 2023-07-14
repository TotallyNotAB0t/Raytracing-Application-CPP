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
    Vector vertex0 = Vector(0, 0, 0);
    Vector vertex1 = Vector(0, 1, 0);
    Vector vertex2 = Vector(0, 0, 1);
    const float EPSILON = 0.000001f;

    Vector edge1 = vertex1 - vertex0;
    Vector edge2 = vertex2 - vertex0;
    Vector vc = ray.vector;
    Vector h = vc.cross(edge2);
    float a = edge1.dot(h);

    if (a > -EPSILON && a < EPSILON)
        return false;  // Le rayon est parallèle au triangle

    float f = 1.0f / a;
    Vector s = Vector(ray.origin.x - vertex0.x, ray.origin.y - vertex0.y, ray.origin.z - vertex0.z);
    float u = f * s.dot(h);

    if (u < 0.0f || u > 1.0f)
        return false;

    Vector q = s.cross(edge1);
    float v = f * vc.dot(q);

    if (v < 0.0f || u + v > 1.0f)
        return false;

    float t = f * edge2.dot(q);

    if (t > EPSILON)
    {
        // Le rayon intersecte le triangle
        impact = ray.origin + t * vc;
        return true;
    }

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

    float u, v, w;
    Vector edge1 = Vector(0, 1, 0) - Vector(0, 0, 0);
    Vector edge2 = Vector(0, 0, 1) - Vector(0, 0, 0);
    Vector pointVec = Vector(lp.x, lp.y, lp.z) - Vector(0, 0, 0);
    float det = edge1.x * edge2.y - edge2.x * edge1.y;

    u = (pointVec.x * edge2.y - pointVec.y * edge2.x) / det;
    v = (pointVec.y * edge1.x - pointVec.x * edge1.y) / det;
    w = 1.0f - u - v;

    float texU = u * 0.0f + v * 1.0f + w * 0.0f;
    float texV = u * 0.0f + v * 0.0f + w * 1.0f;

    return Point(texU, texV, 0);
}