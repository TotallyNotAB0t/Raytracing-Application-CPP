//
// Created by pierr on 21-May-23.
//

#ifndef RTX_SCENE_H
#define RTX_SCENE_H

#include <vector>
#include "Color.h"
#include "../Entities/include/Object.h"
#include "../Entities/include/Light.h"

class Scene {
public:
    Scene();
    Scene(const Color &background, const Color &ambiant);
    ~Scene();

    void setBackground(const Color& c);
    void setAmbiant(const Color& c);
    void addObject(Object* o);
    void addLight(Light* l);
    Color getBackground() const;
    Color getAmbiant() const;
    int nbLights() const;
    const Light* getLight(int index) const;
    Object* closer_intersected(const Ray& ray, Point& impact) const;

private:
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    Color background;
    Color ambiant;
};

#endif //RTX_SCENE_H
