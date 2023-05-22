//
// Created by pierr on 20-May-23.
//

#ifndef RTX_CAMERA_H
#define RTX_CAMERA_H

#include "../../include/Entity.h"

class Camera : public Entity {
public:
    float focal;
    Camera(float focal = 1.0f);
    virtual ~Camera();

    Ray getRay(float x, float y, float ratio) const;
};

#endif //RTX_CAMERA_H
