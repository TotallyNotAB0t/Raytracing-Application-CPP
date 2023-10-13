#ifndef RTX_CAMERA_H
#define RTX_CAMERA_H

#include "Entity.h"

class Camera : public Entity
{
public:
    float focal;
    Camera(float focal = 1.0f);
    Camera(const Camera& camera);
    virtual ~Camera();

    Ray getRay(float x, float y) const;

    void rotateY(float deg) override;
};

#endif //RTX_CAMERA_H
