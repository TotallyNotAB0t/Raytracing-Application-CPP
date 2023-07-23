#include <algorithm>
#include "Scene.h"

Scene::Scene() 
{
    background = Color(0, 0, 0);
    ambiant = Color(0, 0, 0);
}

Scene::Scene(const Color& background, const Color& ambiant) : background(background), ambiant(ambiant) {}

Scene::~Scene() 
{
    for (Object* o : objects) 
    {
        delete o;
    }
    for (Light* l : lights) 
    {
        delete l;
    }
}

void Scene::setBackground(const Color& c) 
{
    background = c;
}

void Scene::setAmbiant(const Color& c) 
{
    ambiant = c;
}

void Scene::addObject(Object* o) 
{
    objects.push_back(o);
}

void Scene::addLight(Light* l) 
{
    lights.push_back(l);
}

Color Scene::getBackground() const 
{
    return background;
}

Color Scene::getAmbiant() const 
{
    return ambiant;
}

int Scene::nbLights() const 
{
    return lights.size();
}

const Light* Scene::getLight(int index) const 
{
    return lights[index];
}

int Scene::nbObject() const
{
    return objects.size();
}

const Object* Scene::getObject(int index) const
{
    return objects[index];
}

Color Scene::renderScene(const Ray& ray, Point& impact) const 
{

    Color color = getBackground();

    double minDist = std::numeric_limits<double>::max();
    for (Object* o : objects)
    {
        Point p;
        if (o->intersect(ray, p))
        {
            double dist = Vector(p - ray.origin).vlength();
            if (dist < minDist)
            {
                minDist = dist;
                impact = p;

                color = getImpactColor(ray, *o, impact, *this); // Use getImpactColor to calculate the Phong illumination
            }
        }
    }
    return color;
}

bool Scene::GetShadow(const Point& impact, const Scene& scene, const Light& light)const
{
    if (!shadows){
        return false;
    }
    bool inShadow = false;
        Ray r = light.getRayFromLight(impact);
        for (int j = 0; j < scene.nbObject(); j++)
        {
            const Object* obj = scene.getObject(j);
            Point p;
            if (obj->intersect(r, p))
            {
                // Check if the intersection point is between the impact point and the light source
                Vector lightDirection = impact - r.origin;
                Vector impactToIntersection = p - r.origin;

                // If the intersection is closer to the impact point than the light source, it is in shadow
                if(impactToIntersection.vlength() < lightDirection.vlength()-0.01)
                {
                    inShadow = true;
                    break;
                }
            }
        }
    return inShadow;
}

Color Scene::getImpactColor(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene)const{
    Material m = obj.getMaterial(impact);

    // Checkboard pattern
    int checkSize = 1; // Size of each checkboard square
    int x = static_cast<int>(impact.x / checkSize);
    int z = static_cast<int>(impact.z / checkSize);
    Color colorPicked = m.kd;
    if (checkboardMat){
        if ((x + z) % 2 == 0) {
            colorPicked = m.kd; // Use the first diffusion color
        } else {
            colorPicked = m.kd2; // Use the second diffusion color
        }
    }

    Ray normal = obj.getNormal(impact,ray.origin);
    Color c = colorPicked*0.3;
    for(int l = 0; l < scene.nbLights(); l++)
    {
        const Light* light = scene.getLight(l);
        if (!GetShadow(impact, scene, *light)){
            Vector lv = light->getVectorToLight(impact).normalized();
            float alpha = lv.dot(normal.vector);
            if(alpha>0)
            {
                c += (light->id).mul(colorPicked) * alpha;
            }
            Vector rm = (2*lv.dot(normal.vector)*normal.vector) - lv;

            float beta = -rm.dot(ray.vector);
            if(beta>0)
            {
                c+=  (light->is).mul(m.ks) * pow(beta, m.shininess);
            }
        }
    }

    Color color = Color(std::clamp(c[0], 0.0f, 1.0f),
                        std::clamp(c[1], 0.0f, 1.0f),
                        std::clamp(c[2], 0.0f, 1.0f));
    return color;

}

Scene::Scene(const Scene &scene) {
    this->objects = scene.objects;
    this->lights = scene.lights;
    this->ambiant = scene.ambiant;
    this->background = scene.background;
}
