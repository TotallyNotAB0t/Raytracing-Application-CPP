//
// Created by pierr on 20-May-23.
//
#include "../include/HRay.h"

HRay::HRay() {
    this->origin = HPoint();
    this->vector = HVector();
}
HRay::HRay(float ox, float oy, float oz, float vx, float vy, float vz) {
    this->origin = HPoint(ox, oy, oz, 1.0f);
    this->vector = HVector(vx, vy, vz, 0.0f);
}

HRay::HRay(const HPoint& o, const HVector& v){
    this->origin = HPoint(o);
    this->vector = HVector(v);
}

HRay::HRay(const HRay& r){
    this->origin = HPoint(r.origin);
    this->vector = HVector(r.vector);
}

HRay& HRay::operator=(const HRay& r) {
    if (this != &r) {
        this->origin = r.origin;
        this->vector = r.vector;
    }
    return *this;
}

HRay::HRay(HRay&& r) noexcept {
    this->origin = r.origin;
    this->vector = r.vector;
}

HRay& HRay::operator=(HRay&& r) noexcept {
    if (this != &r) {
        this->origin = r.origin;
        this->vector = r.vector;
    }
    return *this;
}

HRay::~HRay() {

}

HRay::HRay(const Ray &r) {
    this->vector = HVector(r.vector);
    this->origin = HPoint(r.origin);
}
