#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <vector>
#include <thread>
#include "lib/include/stb_image_write.h"
#include "Classes/Coordinates/include/Matrix.h"
#include "Classes/include/Scene.h"
#include "Classes/Entities/include/Object.h"
#include "Classes/Entities/include/Camera.h"
#include "Classes/Entities/include/Sphere.h"
#include <objbase.h>
#include "shellapi.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Triangle.h"
#include "lib/include/json.hpp"
#include "fstream"
#include "Carre.h"

void renderImage(Scene& scene, Camera& camera, int width, int height, std::vector<unsigned char>& image, int startY, int endY) 
{
    for (int y = startY; y < endY; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            float u = (float)x / (float)width;
            float v = (float)y / (float)height;
            Ray ray = camera.getRay(u, v);
            int index = (y * width + x) * 3;
            Point ptrPoint;
            Color colorToPrint = scene.renderScene(ray, ptrPoint);
            image[index] = colorToPrint[0] * 255.0f;
            image[index + 1] = colorToPrint[1] * 255.0f;
            image[index + 2] = colorToPrint[2] * 255.0f;
        }
    }
}

int main() {
    std::ifstream file("myScene.json");
    if (!file) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    nlohmann::json jsonData;
    file >> jsonData;

    // TODO TROUVER UNE MANIERE MOINS DEGUEU DE PARSE !!!
    for (const auto& object : jsonData) {
        // Getting data
        std::string objectType = object["ObjectType"];
        Object* myObj;
        if (objectType == "Sphere"){
            myObj = new Sphere();
        }
        else if (objectType == "Carre"){
            Carre();
        }
        else if (objectType == "Cube"){
            Cube();
        }
        double positionX = object["PositionX"];
        double positionY = object["PositionY"];
        double positionZ = object["PositionZ"];
        std::string material = object["Material"];
        double scale = object["Scale"];

        // Instanciating objects
        myObj->translate(positionX, positionY, positionZ);
        myObj->scale(scale);
        
    }

    Scene scene;
    scene.setBackground(Color(0.2, 0.2, 0.2));
    scene.shadows = true;
    scene.setAmbiant(Color(0.1, 0.1, 0.1));

    Camera camera(5);
    camera.translate(0, 0, -100);

    Material mat1(Color(1, 0, 0), Color(1, 0, 0), Color(0, 0, 0), 50);
    Material mat2(Color(0, 1, 0), Color(0, 1, 0), Color(1, 1, 1), 10);
    Material mat3(Color(0, 0, 1), Color(0, 0, 1), Color(1, 1, 1), 10);

    Sphere* sphere1 = new Sphere(mat1);
    sphere1->translate(0, 0, 1);

    Sphere* sphere2 = new Sphere(mat2);
    sphere2->translate(-3, 2, 1);

    Sphere* sphere3 = new Sphere(mat3);
    sphere3->translate(2, 0, 1);

    Cylinder* cylinder1 = new Cylinder(mat1);
    cylinder1->translate(-1, 0, 0);
    cylinder1->rotateZ(.5);

    Cube* cube1 = new Cube(mat3);
    cube1->translate(4, 0, 0);

    Light* light1 = new Light();
    light1->id = Color(1, 1, 1);
    light1->is = Color(0.5, 0.5, 0.5);
    light1->translate(-1, 0, -2);

    scene.addLight(light1);

    scene.addObject(sphere2);
    scene.addObject(cube1);
    scene.addObject(cylinder1);

    int width = 500;
    int height = 500;
    std::vector<unsigned char> image(width * height * 3);

    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(numThreads);

    for (int i = 0; i < numThreads; ++i) 
    {
        int startY = (height / numThreads) * i;
        int endY = (i == numThreads - 1) ? height : (height / numThreads) * (i + 1);
        threads[i] = std::thread(renderImage, std::ref(scene), std::ref(camera), width, height, std::ref(image), startY, endY);
    }

    for (auto& thread : threads) 
    {
        thread.join();
    }

    stbi_write_jpg("output.jpg", width, height, 3, image.data(), 100);

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    ShellExecuteA(NULL, "open", ".\\output.jpg", NULL, NULL, SW_SHOWDEFAULT);
    return 0;
}
