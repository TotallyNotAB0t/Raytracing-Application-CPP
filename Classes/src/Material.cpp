//
// Created by pierr on 21-May-23.
//
#include "../include/Material.h"

Material::Material() : ka(Color()), kd(Color()), ks(Color()), shininess(0.0f) {}

Material::Material(const Color& ka, const Color& kd, const Color& ks, float shininess)
        : ka(ka), kd(kd), ks(ks), shininess(shininess) {}
