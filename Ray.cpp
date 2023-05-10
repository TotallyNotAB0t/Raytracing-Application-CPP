//
// Created by pierr on 10-May-23.
//

#include "Ray.h"

Ray::Ray() {
    this->origin = Point();
    this->vector = Vector();
}

Ray::Ray(float ox, float oy, float oz, float vx, float vy, float vz) {
    this->origin = Point(ox, oy, oz);
    this->vector = Vector(vx, vy, vz);
}

Ray::Ray(const Point &o, const Vector &v) {
    this->origin = Point(o);
    this->vector = Vector(v);
}

Ray::Ray(const Ray &r) {
    this->origin = r.origin;
    this->vector = r.vector;
}

Ray& Ray::operator=(const Ray &r) {
    if (this != &r){
        this->origin = r.origin;
        this->vector = r.vector;
    }
    return *this;
}

Ray::Ray(Ray &&r) noexcept {
    this->origin = r.origin;
    this->vector = r.vector;
}

Ray& Ray::operator=(Ray &&r) noexcept {
    if (this != &r){
        this->origin = r.origin;
        this->vector = r.vector;
    }
}

Ray::~Ray() {

}
