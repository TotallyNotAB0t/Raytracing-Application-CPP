//
// Created by pierr on 21-May-23.
//

#include <algorithm>
#include "../include/Scene.h"

Scene::Scene() {
    background = Color(0, 0, 0);
    ambiant = Color(0, 0, 0);
}

Scene::Scene(const Color& background, const Color& ambiant) : background(background), ambiant(ambiant) {}

Scene::~Scene() {
    for (Object* o : objects) {
        delete o;
    }
    for (Light* l : lights) {
        delete l;
    }
}

void Scene::setBackground(const Color& c) {
    background = c;
}

void Scene::setAmbiant(const Color& c) {
    ambiant = c;
}

void Scene::addObject(Object* o) {
    objects.push_back(o);
}

void Scene::addLight(Light* l) {
    lights.push_back(l);
}

Color Scene::getBackground() const {
    return background;
}

Color Scene::getAmbiant() const {
    return ambiant;
}

int Scene::nbLights() const {
    return lights.size();
}

const Light* Scene::getLight(int index) const {
    return lights[index];
}

Color Scene::renderScene(const Ray& ray, Point& impact) const {
    Object* closest = nullptr;
    Color color = getBackground();
    Light* light1 = new Light();
    light1->translate(1, 1, 1);
    double minDist = std::numeric_limits<double>::max();
    for (Object* o : objects) {
        Point p;
        if (o->intersect(ray, p)) {
            double dist = Vector(p - ray.origin).vlength();
            if (dist < minDist) {
                minDist = dist;
                impact = p;
                closest = o;
                color = o->material.kd;
                Vector* lightPos = new Vector(light1->trans(0, 3), light1->trans(1, 3), light1->trans(2, 3));
                //std::cout << lightPos->normalized() << std::endl;
                float n = lightPos->dot(o->getNormal(impact, ray.origin).vector);
                n = std::clamp(n, 0.0f, 1.0f);
                //std::cout << n << std::endl;
                if(!this->shadows){
                    n = ceilf(n);
                }
/*                color[0] = o->getNormal(impact, ray.origin).vector.x * 0.5 + 0.5;
                color[1] = o->getNormal(impact, ray.origin).vector.y * 0.5 + 0.5;
                color[2] = o->getNormal(impact, ray.origin).vector.z * 0.5 + 0.5;*/
                color[0] = color[0] * n;
                color[1] = color[1] * n;
                color[2] = color[2] * n;
            }
        }
    }
    return color;
}
