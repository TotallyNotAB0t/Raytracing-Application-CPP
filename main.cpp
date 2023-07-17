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
    Scene scene;
    scene.setBackground(Color(0.2, 0.2, 0.2));
    scene.shadows = true;
    scene.setAmbiant(Color(0.1, 0.1, 0.1));

    Camera camera(5);
    camera.translate(0, 0, -100);

    std::ifstream file("myScene.txt");
    std::string line;

    Object* myObject;
    std::map<std::string, Material> materialMap;
    std::vector<float> params(10);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string objectType, materialName;
        if (!(iss >> objectType)) {
            std::cerr << "Failed to read object type from line: " << line << std::endl;
            continue;
        }
        // If line is a material
        if (objectType == "Material") {
            if (!(iss >> materialName >> params[0] >> params[1] >> params[2] >> params[3] >> params[4] >> params[5]
                      >> params[6] >> params[7] >> params[8] >> params[9])) {
                std::cerr << "Failed to parse material from line: " << line << std::endl;
                continue;
            }
            materialMap[materialName] = Material(Color(params[0], params[1], params[2]),
                                                 Color(params[3], params[4], params[5]),
                                                 Color(params[6], params[7], params[8]), params[9]);
        } else {
            //If line is an object
            if (!(iss >> materialName >> params[0] >> params[1] >> params[2] >> params[3] >> params[4] >> params[5]
                      >> params[6])) {
                std::cerr << "Failed to parse object from line: " << line << std::endl;
                continue;
            }

            if (materialMap.find(materialName) == materialMap.end()) {
                std::cerr << "Material '" << materialName << "' not found for object: " << line << std::endl;
                continue;
            }

            if (objectType == "Sphere") {
                myObject = new Sphere(materialMap[materialName]);
            } else if (objectType == "Cube") {
                myObject = new Cube(materialMap[materialName]);
            } else if (objectType == "Cylinder") {
                myObject = new Cylinder(materialMap[materialName]);
            } else {
                std::cerr << "Unknown object type: " << objectType << std::endl;
                continue;
            }
            myObject->translate(params[0], params[1], params[2]);
            myObject->rotateX(params[3]);
            myObject->rotateY(params[4]);
            myObject->rotateZ(params[5]);
            scene.addObject(myObject);
        }
    }

    Light* light1 = new Light();
    light1->id = Color(1, 1, 1);
    light1->is = Color(0.5, 0.5, 0.5);
    light1->translate(-1, 0, -2);

    scene.addLight(light1);

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
