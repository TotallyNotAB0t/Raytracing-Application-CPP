#ifndef RTX_CARRE_H
#define RTX_CARRE_H

#include "Object.h"

class Carre : public Object
{
public:
    Carre() : Object(){};
    Carre(const Material& mat) : Object(mat) {};
    Carre(const Carre& carre);
    ~Carre();

    bool intersect(const Ray& ray, Point& impact)const override;

    Ray getNormal(const Point &p, const Point &o) const;

    Point getTextureCoordinates(const Point &p) const;
};

#endif //RTX_CARRE_H
