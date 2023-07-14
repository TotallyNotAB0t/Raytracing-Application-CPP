#ifndef RTX_MATERIAL_H
#define RTX_MATERIAL_H

#include "Color.h"

class Material 
{
public:
    Color ka;
    Color kd;
    Color ks;
    float shininess;

    Material();
    Material(const Color& ka, const Color& kd, const Color& ks, float shininess);
};

#endif //RTX_MATERIAL_H
