#include "Light.h"

Light::Light() : Entity(), id(Color()), is(Color()) {}

Light::Light(const Point& p, const Color& id, const Color& is) : id(id), is(is)
{
    translate(p.x, p.y, p.z);
    trans = Matrix()*trans;
    transInv=trans.inverse();
}

Ray Light::getRayToLight(const Point& p) const
{
    Point pLocal = globalToLocal(p);
    Point originLocal(0, 0, 0);
    Vector vectorLocal = getVectorToLight(p);
    Ray rayLocal = Ray(pLocal, vectorLocal);
    return localToGlobal(rayLocal);
}

Ray Light::getRayFromLight(const Point& p) const
{
    Point pLocal = globalToLocal(p);
    Point originLocal(0, 0, 0);
    Vector vectorLocal = getVectorFromLight(p);
    Ray rayLocal = Ray(originLocal, vectorLocal);
    return localToGlobal(rayLocal);
}

Vector Light::getVectorToLight(const Point& p) const
{
    Point pLocal = globalToLocal(p);
    Point originLocal(0, 0, 0);
    Vector vectorLocal = originLocal - pLocal;
    return vectorLocal.normalized();
}

Vector Light::getVectorFromLight(const Point& p) const
{
    Point pLocal = globalToLocal(p);
    Point originLocal(0, 0, 0);
    Vector vectorLocal = pLocal - originLocal;
    return vectorLocal.normalized();
}

Light::Light(const Light &light) {
    this->trans = light.trans;
    this->transInv = light.transInv;
    this->id = light.id;
    this->is = light.is;
}
