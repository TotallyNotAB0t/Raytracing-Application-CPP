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

Color Scene::renderScene(const Ray& ray, Point& impact) const 
{
    Color color = getBackground();
    Light* light1 = new Light();
    light1->translate(0, 0, 0);
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
                color = o->material.kd;
                Vector* lightPos = new Vector(light1->trans(0, 3), light1->trans(1, 3), light1->trans(2, 3));
                float n = lightPos->dot(o->getNormal(impact, ray.origin).vector);
                n = std::clamp(n, 0.0f, 1.0f);
                if (!this->shadows) 
                {
                    n = ceilf(n);
                }
                /*color[0] = o->getNormal(impact, ray.origin).vector.x * 0.5 + 0.5;
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

Color Scene::getImpactColor(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene) const 
{
    Material m = obj.getMaterial(impact);
    Ray normal = obj.getNormal(impact, ray.origin);
    Color c = m.ka.mul(scene.getAmbiant());
    for (int l = 0; l < scene.nbLights(); l++) 
    {
        const Light* light = scene.getLight(l);
        Vector lv = light->getVectorToLight(impact);
        float alpha = lv.dot(normal.vector);
        if (alpha > 0)
        {
            c += (light->id).mul(m.kd) * alpha;
        }

        Vector rm = (2 * lv.dot(normal.vector) * normal.vector) - lv;

        float beta = -rm.dot(ray.vector);
        if (beta > 0)
        {
            c += (light->is).mul(m.ks) * pow(beta, m.shininess);
        }
    }
    return c;
}