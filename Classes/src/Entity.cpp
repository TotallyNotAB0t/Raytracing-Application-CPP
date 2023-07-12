//
// Created by pierr on 20-May-23.
//
#include "../include/Entity.h"

#include <cmath>

Entity::Entity() : trans(Matrix()) {}

Entity::~Entity() {}

void Entity::translate(float x, float y, float z){
    Matrix m;
    m(0, 3) = x;
    m(1, 3) = y;
    m(2, 3) = z;
    trans=m*trans;
    transInv=trans.inverse();
}

void Entity::scale(float factor){
    Matrix m;
    m(0, 0) = factor;
    m(1, 1) = factor;
    m(2, 2) = factor;
    trans = m*trans;
    transInv=trans.inverse();
}

void Entity::rotateX(float deg){
    Matrix m;
    float c  = cos(deg);
    float s  = sin(deg);
    m(1,1) = c;
    m(1,2) = -s;
    m(2,1) = s;
    m(2,2) = c;
    trans=m*trans;
    transInv=trans.inverse();
}

void Entity::rotateY(float deg){
    Matrix m;
    float c  = cos(deg);
    float s  = sin(deg);
    m(0,0) = c;
    m(0,2) = s;
    m(2,0) = -s;
    m(2,2) = c;
    trans = m*trans;
    transInv=trans.inverse();
}

void Entity::rotateZ(float deg){
    Matrix m;
    float c = cos(deg);
    float s = sin(deg);
    m(0,0) = c;
    m(0,1) = -s;
    m(1,0) = s;
    m(1,1) = c;
    trans=m*trans;
    transInv=trans.inverse();
}

Point Entity::localToGlobal(const Point& p)const{
    HPoint hp(p);
    HPoint temp(transInv * hp);
/*    std::cout << "=============" << std::endl;
    std::cout << "trans inv : "<< std::endl << transInv << std::endl;
    std::cout << "HPoint : " << hp << std::endl;
    std::cout << "Temp : " << temp << std::endl;*/
    Point res(temp.x, temp.y, temp.z);
    return res;
}

Vector Entity::localToGlobal(const Vector &v) const {
    HVector hv(v);
    HVector temp(transInv * hv);
    Vector res(temp.x, temp.y, temp.z);
    return res;
}

Ray Entity::localToGlobal(const Ray &r) const {
    Ray res(localToGlobal(r.origin), localToGlobal(r.vector));
    return res;
}

Point Entity::globalToLocal(const Point& p) const {
    HPoint hp(p);
    HPoint temp(trans * hp);
    Point res(temp.x, temp.y, temp.z);
    return res;
}

Vector Entity::globalToLocal(const Vector& v) const {
    HVector hv(v);
    HVector temp(trans * hv);
    Vector res(temp.x, temp.y, temp.z);
    return res;
}

Ray Entity::globalToLocal(const Ray& r) const {
    Ray res(globalToLocal(r.origin), globalToLocal(r.vector));
    return res;
}
