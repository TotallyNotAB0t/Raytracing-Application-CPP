#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <vector>
#include "lib/include/stb_image_write.h"
#include "Objects/include/InstantiableObject.h"
#include "Classes/Coordinates/include/Matrix.h"
#include "Classes/include/Scene.h"
#include "Classes/Entities/include/Object.h"
#include "Classes/Entities/include/Camera.h"
#include "Classes/Entities/include/Sphere.h"
#include <objbase.h>
#include "shellapi.h"
#include "Classes/Entities/include/Cube.h"

int main() 
{
    Scene scene;
    scene.setBackground(Color(0.2, 0.2, 0.2));
    scene.shadows = true;
    scene.setAmbiant(Color(0.1, 0.1, 0.1));

    Camera camera(5);
    camera.translate(0, 0, -100);

    Material mat1(Color(0.2, 0.2, 0.8), Color(1, 0, 0), Color(1.0, 1.0, 1.0), 50);
    Material mat2(Color(0.2, 0.8, 0.8), Color(0, 1, 0), Color(1.0, 1.0, 1.0), 20);
    Material mat3(Color(1.0, 1.0, 1.0), Color(0, 0, 1), Color(1.0, 1.0, 1.0), 20);

    Sphere* sphere1 = new Sphere(mat1);
    sphere1->translate(0, 0, 1);

    Sphere* sphere2 = new Sphere(mat2);
    sphere2->translate(-3, 0, 1);

    Sphere* sphere3 = new Sphere(mat3);
    sphere3->translate(2, 0, 1);

    Cube* cube1 = new Cube(mat3);
    cube1->translate(0, 0, 0);
    cube1->rotateY(.5f);
    cube1->rotateX(.5f);

    Light* light1 = new Light();
    light1->translate(1, 1, 1);

    //scene.addLight(light1);
    scene.addObject(sphere1);
    //scene.addObject(cube1);

    int width = 500;
    int height = 500;
    std::vector<unsigned char> image(width * height * 3);

    for (int y = 0; y < height; ++y) 
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

    stbi_write_jpg("output.jpg", width, height, 3, image.data(), 100);

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    ShellExecuteA(NULL, "open", ".\\output.jpg", NULL, NULL, SW_SHOWDEFAULT);
    return 0;
}
