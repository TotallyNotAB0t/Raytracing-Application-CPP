//
// Created by pierr on 13-May-23.
//
#include "../include/InstantiableObject.h"
#include <fstream>
#include <iostream>
#include "../include/Sphere.h"
#include "../include/Plane.h"
#include "../include/ObjectUtiliy.h"

std::vector<InstantiableObject*> ObjectUtility::createObjectsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return std::vector<InstantiableObject*>();
    }

    std::vector<InstantiableObject*> objects;

    std::string objectType;
    while (file >> objectType) {
        if (objectType == "Sphere") {
            float radius, posX, posY, posZ;
            file >> radius >> posX >> posY >> posZ;
            Vector position(posX, posY, posZ);
            objects.push_back(new Sphere(radius, position));
        } else if (objectType == "Plane") {
            int width, height;
            float posX, posY, posZ;
            file >> width >> height >> posX >> posY >> posZ;
            Vector position(posX, posY, posZ);
            objects.push_back(new Plane(width, height, position));
        } else {
            std::cerr << "Unknown object type: " << objectType << std::endl;
        }
    }

    file.close();

    return objects;
}
