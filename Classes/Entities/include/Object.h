#ifndef RTX_OBJECT_H
#define RTX_OBJECT_H

#include "Entity.h"
#include "Material.h"

class Object : public Entity 
{
public:
    Material material;
    Object() 
    {
        trans = Matrix();
        transInv = trans.inverse();
    }
    explicit Object(const Material& mat)
    {
        trans = Matrix();
        transInv = trans.inverse();
        material = mat;
    };

    virtual Point getTextureCoordinates(const Point& p) const = 0;
    virtual Ray getNormal(const Point &p, const Point &o) const = 0;
    virtual bool intersect(const Ray& ray, Point& impact) const = 0;
    virtual Material getMaterial(const Point& point) const 
    {
        return this->material;
    }
};

#endif //RTX_OBJECT_H
