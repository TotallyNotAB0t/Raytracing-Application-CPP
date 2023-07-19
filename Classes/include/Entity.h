#ifndef RTX_ENTITY_H
#define RTX_ENTITY_H

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Matrix.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Entity 
{
public:
    Entity();
    virtual ~Entity();

    void translate(float x, float y, float z);
    void scale(float factor);
    void rotateX(float deg);
    virtual void rotateY(float deg);
    void rotateZ(float deg);

    Point localToGlobal(const Point& p) const;
    Vector localToGlobal(const Vector& v) const;
    Ray localToGlobal(const Ray& r) const;

    Point globalToLocal(const Point& p) const;
    Vector globalToLocal(const Vector& v) const;
    Ray globalToLocal(const Ray& r) const;

public:
    Matrix trans;
    Matrix transInv;
};

#endif //RTX_ENTITY_H

