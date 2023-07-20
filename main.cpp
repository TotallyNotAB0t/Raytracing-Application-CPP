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
#include <map>
#include <sstream>
#include "shellapi.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Triangle.h"
#include "fstream"
#include "Carre.h"
#include "Plan.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gopt.h"

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

// PLACEHOLDER POUR SHADOW
static bool shadow = false;

//int main (int argc, char **argv)
//{
//    struct option options[5];
//
//    options[0].long_name  = "scene";
//    options[0].short_name = 's';
//    options[0].flags      = GOPT_ARGUMENT_REQUIRED;
//
//    options[1].long_name  = "height";
//    options[1].short_name = 'h';
//    options[1].flags      = GOPT_ARGUMENT_REQUIRED;
//
//    options[2].long_name  = "width";
//    options[2].short_name = 'w';
//    options[2].flags      = GOPT_ARGUMENT_REQUIRED;
//
//    options[3].long_name  = "output";
//    options[3].short_name = 'o';
//    options[3].flags      = GOPT_ARGUMENT_REQUIRED;
//
//    options[4].flags      = GOPT_LAST;
//
//    argc = gopt (argv, options);
//
//    gopt_errors (argv[0], options);
//
//    if (options[0].count)
//    {
//        std::cout << "MANAL" << std::endl;
//        //fprintf (stdout, "see the manual\n");
//        //exit (EXIT_SUCCESS);
//    }
//
//    if (options[1].count)
//    {
//        fprintf (stdout, "version 1.0\n");
//        //exit (EXIT_SUCCESS);
//    }
//
//    if (options[2].count >= 1)
//    {
//        fputs ("being verbose\n", stderr);
//    }
//
//    if (options[2].count >= 2)
//    {
//        fputs ("being very verbose\n", stderr);
//    }
//
//    if (options[3].count) {
//        std::cout << options[3].argument << std::endl;
//    }
//
//    return 0;
//}

int main(int argc, char** argv) {

    // Settings
    std::string fileName = "myScene";
    std::string outputFileName = "output";
    int width = 500;
    int height = 500;

    // Reading arguments if any
    struct option options[6];

    options[0].long_name  = "scene";
    options[0].short_name = 's';
    options[0].flags      = GOPT_ARGUMENT_REQUIRED;

    options[1].long_name  = "height";
    options[1].short_name = 'h';
    options[1].flags      = GOPT_ARGUMENT_REQUIRED;

    options[2].long_name  = "width";
    options[2].short_name = 'w';
    options[2].flags      = GOPT_ARGUMENT_REQUIRED;

    options[3].long_name  = "output";
    options[3].short_name = 'o';
    options[3].flags      = GOPT_ARGUMENT_REQUIRED;

    options[4].long_name  = "shadows";
    options[4].short_name = 'd';
    options[4].flags      = GOPT_ARGUMENT_FORBIDDEN;

    options[5].flags      = GOPT_LAST;

    gopt(argv, options);

    gopt_errors(argv[0], options);

    if (options[0].count)
    {
        fileName = options[0].argument;
    }

    fileName += ".txt";
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file : " << fileName << ", opening myScene.txt instead." << std::endl;
        file.close();
        file.open("myScene.txt");
    }

    if (options[1].count)
    {
        height = atoi(options[1].argument);
        if (height <= 0)
        {
            std::cout << options[1].long_name << " argument is not correct. Defaulting to 500." << std::endl;
            height = 500;
        }
    }

    if (options[2].count)
    {
        width = atoi(options[2].argument);
        if (width <= 0)
        {
            std::cout << options[2].long_name << " argument is not correct. Defaulting to 500." << std::endl;
            width = 500;
        }
    }

    if (options[3].count)
    {
        outputFileName = options[3].argument;
    }
    outputFileName += ".jpg";

    if (options[4].count)
    {
        shadow = true;
    }

    // Main loop
    Scene scene;
    scene.setBackground(Color(0.2, 0.2, 0.2));
    scene.shadows = true;
    scene.setAmbiant(Color(0.1, 0.1, 0.1));

    Camera camera(5);
    camera.translate(0, 0, -100);

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
        }
        // If the line is a light
        else if (objectType == "Light") {
            if (!(iss >> params[0] >> params[1] >> params[2] >> params[3] >> params[4] >> params[5] >> params[6] >> params[7] >> params[8])) {
                std::cerr << "Failed to parse light from line: " << line << std::endl;
                continue;
            }
            Light* light = new Light(Point(params[0], params[1], params[2]),
                                     Color(params[3], params[4], params[5]),
                                     Color(params[6], params[7], params[8]));
            scene.addLight(light);
        }
        // If the line is an object
        else {
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
            } else if (objectType == "Plan") {
                myObject = new Plan(materialMap[materialName]);
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
    file.close();

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

    const char* charFileName = outputFileName.c_str();

    std::string pathName = ".\\";
    pathName += outputFileName;

    const char* pathCharFileName = pathName.c_str();

    stbi_write_jpg(charFileName, width, height, 3, image.data(), 100);

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    ShellExecuteA(NULL, "open", pathCharFileName, NULL, NULL, SW_SHOWDEFAULT);
    return 0;
}
