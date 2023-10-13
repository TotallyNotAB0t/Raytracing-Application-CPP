#ifndef RTX_LIGHT_H
#define RTX_LIGHT_H

#include "Entity.h"
#include "Color.h"

class Light : public Entity
{
public:
    Color id;
    Color is;

    Light();
    Light(const Light& light);
    Light(const Point& p, const Color& id, const Color& is);

    Ray getRayToLight(const Point& p) const;
    Ray getRayFromLight(const Point& p) const;
    Vector getVectorToLight(const Point& p) const;
    Vector getVectorFromLight(const Point& p) const;
};

#endif //RTX_LIGHT_H
