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
    /*Color color = getBackground();

    Light* light1 = this->lights[0];
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
                Vector lightPos = Vector(light1->trans(0, 3), light1->trans(1, 3), light1->trans(2, 3)).normalized();
                float n = lightPos.dot(o->getNormal(impact, ray.origin).vector);
                n = std::clamp(n, 0.0f, 1.0f);
                if (!this->shadows) 
                {
                    n = ceilf(n);
                }
                *//*color[0] = o->getNormal(impact, ray.origin).vector.x * 0.5 + 0.5;
                color[1] = o->getNormal(impact, ray.origin).vector.y * 0.5 + 0.5;
                color[2] = o->getNormal(impact, ray.origin).vector.z * 0.5 + 0.5;*//*
                color[0] = color[0] * n;
                color[1] = color[1] * n;
                color[2] = color[2] * n;
            }
        }
        }*/

    Color color = getBackground();

    Light* light1 = this->lights[0];
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
    //return color;
}

Color Scene::getImpactColor(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene)const{
    Material m = obj.getMaterial(impact);
    Ray normal = obj.getNormal(impact,ray.origin);
    Color c = m.ka.mul(scene.getAmbiant());
    for(int l = 0; l < scene.nbLights(); l++)
    {
        const Light* light = scene.getLight(l);
        Vector lv = light->getVectorToLight(impact);
        float alpha = lv.dot(normal.vector);
        if(alpha>0)
        {
            c += (light->id).mul(m.kd) * alpha;
        }
        Vector rm = (2*lv.dot(normal.vector)*normal.vector) - lv;

        float beta = -rm.dot(ray.vector);
        if(beta>0)
        {
            c+=  (light->is).mul(m.ks) * pow(beta, m.shininess);
        }

    }

    Color color = Color(std::clamp(c[0], 0.0f, 1.0f),
                        std::clamp(c[1], 0.0f, 1.0f),
                        std::clamp(c[2], 0.0f, 1.0f));
    return color;

}

/*
Color Scene::getImpactColor(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene) const
{
/*Ray normpos = obj.getNormal(impact, ray.origin);
    Vector norm = normpos.vector.normalized();
    Point pos = normpos.origin;

    Material mat = obj.getMaterial(pos);

    Color ambient = scene.getAmbiant().mul(mat.ka);

    Color diffuse;
    Color specular;

    for (int i = 0; i < scene.nbLights(); i++)
    {
        Vector lightDir = scene.getLight(i)->getVectorToLight(pos).normalized();
        float lambert = std::max(norm.dot(lightDir), 0.0f);
        Color lightColor = scene.getLight(i)->id;
        diffuse += lightColor.mul(Color(lambert,lambert,lambert));

        Vector reflected = (2 * norm.dot(lightDir) * norm) - lightDir;
        Vector view = Vector(ray.origin - impact).normalized();
        float specularFactor = pow(std::max(view.dot(reflected), 0.0f),mat.shininess);
        specular += lightColor.mul(pow(specularFactor, mat.shininess));
        //specular[1] = specular[0];
        //specular[2] = specular[0];
    }
    Color color = Color(std::clamp((ambient + diffuse.mul(mat.kd) + specular.mul(mat.ks))[0], 0.0f, 1.0f),
                        std::clamp((ambient + diffuse.mul(mat.kd) + specular.mul(mat.ks))[1], 0.0f, 1.0f),
                        std::clamp((ambient + diffuse.mul(mat.kd) + specular.mul(mat.ks))[2], 0.0f, 1.0f));

    return color;*//*

}*/
