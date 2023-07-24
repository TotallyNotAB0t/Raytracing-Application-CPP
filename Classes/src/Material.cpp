#include "Material.h"

Material::Material() : ka(Color()), kd(Color()), ks(Color()), shininess(0.0f) {
    this->kd2 = Color(1, 1, 1);
}

Material::Material(const Color& ka, const Color& kd, const Color& ks, float shininess) : ka(ka), kd(kd), ks(ks), shininess(shininess) {
    this->kd2 = Color(1, 1, 1);
}
