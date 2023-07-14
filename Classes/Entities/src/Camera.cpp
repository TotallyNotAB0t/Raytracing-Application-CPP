#include "Camera.h"

Ray Camera::getRay(float x, float y) const 
{
    Point origin(x * 2 - 1, y * 2 - 1, 0);
    Point pointFocal(0, 0, this->focal);
    Vector dir(origin[0], origin[1], -pointFocal[2]);    
    dir = this->localToGlobal(dir);
    std::cout << dir << std::endl;
    dir = dir.normalized();
    origin = this->localToGlobal(origin);
    Ray r(origin, dir);
    return r;
}

Camera::Camera(float focal) 
{
    this->focal = focal;
}

Camera::~Camera() 
{

}
