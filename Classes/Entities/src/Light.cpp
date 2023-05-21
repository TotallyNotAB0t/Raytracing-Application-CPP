//
// Created by pierr on 21-May-23.
//
#include "../include/Light.h"

Light::Light() : Entity(), id(Color()), is(Color()) {}

Light::Light(const Point& p, const Color& id, const Color& is) : id(id), is(is) {
    translate(p.x, p.y, p.z);
}

Ray Light::getRayToLight(const Point& p) const {
    Point pLocal = globalToLocal(p);
    Point originLocal(0, 0, 0);
    Vector vectorLocal = getVectorToLight(pLocal);
    Ray rayLocal = Ray(originLocal, vectorLocal);
    return localToGlobal(rayLocal);
}

Ray Light::getRayFromLight(const Point& p) const {
    Point pLocal = globalToLocal(p);
    Point originLocal(0, 0, 0);
    Vector vectorLocal = getVectorFromLight(pLocal);
    Ray rayLocal = Ray(originLocal, vectorLocal);
    return localToGlobal(rayLocal);
}

Vector Light::getVectorToLight(const Point& p) const {
    Point pLocal = globalToLocal(p);
    Point originLocal(0, 0, 0);
    Vector vectorLocal = originLocal - pLocal;
    return vectorLocal.normalized();
}

Vector Light::getVectorFromLight(const Point& p) const {
    Point pLocal = globalToLocal(p);
    Point originLocal(0, 0, 0);
    Vector vectorLocal = pLocal - originLocal;
    return vectorLocal.normalized();
}
