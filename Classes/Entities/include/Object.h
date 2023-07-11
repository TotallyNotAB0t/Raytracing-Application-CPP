//
// Created by pierr on 21-May-23.
//

#ifndef RTX_OBJECT_H
#define RTX_OBJECT_H

#include "../../include/Entity.h"
#include "../../include/Material.h"

class Object : public Entity {
private:
    //Material material;
public:
    Material material;
    Object() {
        trans = Matrix();
        transInv = trans.inverse();
    }
    explicit Object(const Material& mat){
        trans = Matrix();
        transInv = trans.inverse();
        material = mat;
    };

    virtual Point getTextureCoordinates(const Point& p) const = 0;
    virtual Ray getNormal(const Point &p, const Point &o) const = 0;
    virtual bool intersect(const Ray& ray, Point& impact) const = 0;
};

#endif //RTX_OBJECT_H
