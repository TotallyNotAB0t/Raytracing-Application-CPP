//
// Created by pierr on 20-May-23.
//

#ifndef RTX_CARRE_H
#define RTX_CARRE_H

#include "Object.h"

class Carre : public Object {
    bool intersect(const Ray& ray, Point& impact)const override;
};

#endif //RTX_CARRE_H
