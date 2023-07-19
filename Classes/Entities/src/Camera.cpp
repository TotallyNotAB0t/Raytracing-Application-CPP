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
void Camera::rotateY(float deg)
{
    Matrix m;
    deg *= -M_PI/180;
    float c  = cos(deg);
    float s  = sin(deg);
    m(0,0) = c;
    m(0,2) = s;
    m(2,0) = -s;
    m(2,2) = c;
    trans = m*trans;
    transInv=trans.inverse();
}

Camera::~Camera() 
{

}
