//
// Created by pierr on 20-May-23.
//
#include "../include/Camera.h"

Ray Camera::getRay(float x, float y, float ratio) const {
    Ray r(-1+2*x*ratio,-1+2*y,0,0,0,0);
    Point foc(0,0,focal);
    r.vector = (r.origin - foc);
    r = localToGlobal(r);
    return r.normalized();
}

Camera::Camera(float focal) {
    this->focal = focal;
}

Camera::~Camera() {

}
