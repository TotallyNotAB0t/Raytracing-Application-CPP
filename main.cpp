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
#include <cxxopts.hpp>
#include <iomanip>

void renderImage(Scene& scene, Camera& camera, int width, int height, std::vector<unsigned char>& image, int startY, int endY, int threadID, std::vector<int>& tab)
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
            tab[threadID]++;
        }
    }
}

int main(int argc, char** argv) {

    cxxopts::Options options("RTX", "Arguments of the RTX project");

    options.add_options()
        ("s,scene", "The name of the scene to be loaded", cxxopts::value<std::string>()->default_value("myScene"))
        ("o,output", "The name of the file to create", cxxopts::value<std::string>()->default_value("output"))
        ("h,height", "The height of the image to create", cxxopts::value<int>()->default_value("500"))
        ("w,width", "The width of the image to create", cxxopts::value<int>()->default_value("500"))
        ("d,shadows", "Should the shadows in the scene be activated", cxxopts::value<bool>()->default_value("false"))
        ("x,checkboard", "Should we use a checkboard material", cxxopts::value<bool>()->default_value("false"))
        ("e,help", "Print the help")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    // Argument parsing
    std::string fileName = result["scene"].as<std::string>();
    fileName += ".txt";
    std::string outputFileName = result["output"].as<std::string>();
    outputFileName += ".jpg";
    int width = result["width"].as<int>();
    int height = result["height"].as<int>();

    // Argument check
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file : " << fileName << ", opening myScene.txt instead." << std::endl;
        file.close();
        file.open("myScene.txt");
    }

    if (height <= 0)
    {
        std::cerr << "height argument is not correct. Defaulting to 500." << std::endl;
        height = 500;
    }

    if (width <= 0)
    {
        std::cerr << "width argument is not correct. Defaulting to 500." << std::endl;
        width = 500;
    }

    // Main loop
    Scene scene;
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Light>> lights;
    scene.setBackground(Color(0.2, 0.2, 0.2));
    scene.shadows = result["shadows"].as<bool>();
    scene.checkboardMat = result["checkboard"].as<bool>();

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
            auto light = std::make_unique<Light>(Point(params[0], params[1], params[2]),
                                                 Color(params[3], params[4], params[5]),
                                                 Color(params[6], params[7], params[8]));
            scene.addLight(light.get());
            lights.push_back(std::move(light));
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
            } else if (objectType == "Carre") {
                myObject = new Carre(materialMap[materialName]);
            } else if (objectType == "Cylinder") {
                myObject = new Cylinder(materialMap[materialName]);
            } else if (objectType == "Plan") {
                myObject = new Plan(materialMap[materialName]);
            } else if (objectType == "Triangle") {
                myObject = new Triangle();
                myObject->material = materialMap[materialName];
            } else {
                std::cerr << "Unknown object type: " << objectType << std::endl;
                continue;
            }
            myObject->translate(params[0], params[1], params[2]);
            myObject->rotateX(params[3]);
            myObject->rotateY(params[4]);
            myObject->rotateZ(params[5]);
            myObject->scale(params[6]);
            objects.push_back(std::unique_ptr<Object>(myObject));
            scene.addObject(myObject);
        }
    }
    file.close();

    std::vector<unsigned char> image(width * height * 3);

    int numThreads = std::thread::hardware_concurrency();
    std::vector<int> finishedPercentage;
    std::vector<std::thread> threads(numThreads);

    for (int i = 0; i < numThreads; ++i)
    {
        int startY = (height / numThreads) * i;
        int endY = (i == numThreads - 1) ? height : (height / numThreads) * (i + 1);
        int threadID = i;
        finishedPercentage.push_back(1);
        threads[i] = std::thread(renderImage, std::ref(scene), std::ref(camera), width, height, std::ref(image), startY, endY, threadID, std::ref(finishedPercentage));
    }
    int globalFinishedPercent = 0;
    while (globalFinishedPercent <= (width * height))
    {
        globalFinishedPercent = 0;
        for (int i = 0; i < finishedPercentage.size(); ++i) {
            globalFinishedPercent += finishedPercentage[i];
        }
        std::cout << "Percentage : " << std::fixed << std::setprecision(2) << ((float)globalFinishedPercent / (width * height)) * 100 << '%' << std::endl;
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
