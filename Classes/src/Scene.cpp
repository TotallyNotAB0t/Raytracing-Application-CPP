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
                Vector L = Vector(1, 0, 0);
                float n = L.dot(o->getNormal(impact, ray.origin).vector.normalized());
                n = std::clamp(n, 0.0f, 1.0f);
                color[0] = color[0] * n;
                color[1] = color[1] * n;
                color[2] = color[2] * n;
            }
        }
    }
    return color;
}
