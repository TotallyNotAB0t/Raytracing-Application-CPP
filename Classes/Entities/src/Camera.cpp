#include "Camera.h"

Ray Camera::getRay(float x, float y) const 
{
    Ray r(-(-1.0f+2.0f*x),-1.0f+2.0f*y,0,0,0,0);
    Point foc(0,0,focal);
    r.vector = (r.origin - foc);
    //std::cout << r.origin << " " << r.vector << std::endl;
    r = localToGlobal(r);
    //std::cout << r.origin << " " << r.vector << std::endl;
    return r.normalized();
}

Camera::Camera(float focal) 
{
    this->focal = focal;
}

Camera::~Camera() 
{

}
