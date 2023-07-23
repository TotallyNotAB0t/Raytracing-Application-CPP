#ifndef RTX_SCENE_H
#define RTX_SCENE_H

#include <vector>
#include "Color.h"
#include "Object.h"
#include "Light.h"

class Scene 
{
public:
    bool checkboardMat;
    bool shadows;
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
    int nbObject() const;
    const Light* getLight(int index) const;
    const Object* getObject(int index) const;
    Color renderScene(const Ray& ray, Point& impact) const;

private:
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    Color background;
    Color ambiant;

    Color getImpactColor(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene) const;

    bool GetShadow(const Point &impact, const Scene &scene, const Light& light) const;
};

#endif //RTX_SCENE_H
