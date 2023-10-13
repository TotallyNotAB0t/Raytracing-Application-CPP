#ifndef RTX_MATERIAL_H
#define RTX_MATERIAL_H

#include "Color.h"

class Material
{
public:
    Color ka;//ambiant
    Color kd;//diffusion
    Color kd2;
    Color ks;//specular
    float shininess;

    Material();
    Material(const Color& ka, const Color& kd, const Color& ks, float shininess);
    Material(const Material& mat);
    ~Material();
};

#endif //RTX_MATERIAL_H
