#ifndef RTX_CARRE_H
#define RTX_CARRE_H

#include "Object.h"

class Carre : public Object 
{
public:
    Carre() : Object() {};
    bool intersect(const Ray& ray, Point& impact)const override;
    ~Carre();

     Point getTextureCoordinates(const Point& p) const override;
     Ray getNormal(const Point &p, const Point &o) const override;
};

#endif //RTX_CARRE_H
