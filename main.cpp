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

int main() {

    //Vector tests
    /*    Vector test(1, 2, 3);
    Vector testt = test + test;
    std::cout << testt << std::endl;
    std::cout << -testt << std::endl;
    Vector testtt = testt - test;
    std::cout << testtt << std::endl;
    Point p(2,2,6.5);
    std::cout << p << std::endl;
    std::cout << test[2] << std::endl;*/

    //Matrix test
/*    Matrix mattt = Matrix(0, 0, -1, 2,
                          0, 1, 0, 0,
                          9, 0, 0, 0,
                          0, 0, 0, 1);
    std::cout << mattt << std::endl;
    mattt = mattt.inverse();
    std::cout << mattt << std::endl;

    Matrix mat = Matrix(1, 1, 1, 1,
                        2, 2, 2, 2,
                        3, 3, 3, 3,
                        4, 4, 4, 4);

    Matrix mat33 = Matrix(2, 2, 2, 2,
                          3, 3, 3, 3,
                          4, 4, 4, 4,
                          5, 5, 5, 5);

    std::cout << mat * mat33 << std::endl;
    std::cout << mat << std::endl;

    HPoint hp = HPoint(1, 2, 3, 1);

    std::cout << hp << std::endl;

    //std::cout << hp.x << std::endl;
    HPoint res = mat * hp;
    //std::cout << res.x << std::endl;

    std::cout << res << std::endl;*/

    // Object creation test
/*    std::string filename = "test_objects.txt";
    std::vector<InstantiableObject*> objects = ObjectUtility::createObjectsFromFile(filename);

    for(const auto& obj : objects){
        if (Sphere* sphere = dynamic_cast<Sphere*>(obj)) {
            std::cout << "Sphere radius : " << sphere->radius << " position : (" << sphere->position[0] << ", "
                      << sphere->position[1] << ", " << sphere->position[2] << ')' << std::endl;
        }
        if (PlaneObj* plane = dynamic_cast<PlaneObj*>(obj)){
            std::cout << "PlaneObj position width : " << plane->width << ", height : " << plane->height << ", position : ("
            << plane->position[0] << ", " << plane->position[1] << ", " << plane->position[2] <<  ')' << std::endl;
        }
    }*/

    // Test scene creation
    Scene scene;
    scene.setBackground(Color(0.2, 0.2, 0.2));
    scene.shadows = true;
    //scene.setAmbiant(Color(0.1, 0.1, 0.1));

    // Camera creation
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

    Light* light1 = new Light();
    light1->translate(1, 1, 1);
    scene.addLight(light1);

    //camera.rotateY(.2f);

/*
    Cube* cube1 = new Cube(mat1);
    cube1->translate(-3, 0, 5);
*/

    scene.addObject(sphere1);
    scene.addObject(sphere2);
    scene.addObject(sphere3);
    //scene.addObject(sphere2);
    //scene.addObject(cube1);

    // Ajouter une lumière à la scène
    /*Light* light1 = new Light(Point(0, 5, 0), Color(1.0, 1.0, 1.0), Color(1.0, 1.0, 1.0));
    scene.addLight(light1);*/

    // Rendu de l'image
    int width = 500;
    int height = 500;
    std::vector<unsigned char> image(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float u = float(x) / float(width);
            float v = float(y) / float(height);
            Ray ray = camera.getRay(u, v);

            int index = (y * width + x) * 3;
            bool isIntersect = false;
            Point ptrPoint;
            //isIntersect = scene.renderScene(ray, ptrPoint);
            //isIntersect = sphere1->intersect(ray, ptrPoint);

            Color colorToPrint = scene.renderScene(ray, ptrPoint);
            image[index] = colorToPrint[0] * 255.0f;
            image[index + 1] = colorToPrint[1] * 255.0f;
            image[index + 2] = colorToPrint[2] * 255.0f;
/*            if (isIntersect){
                Vector L = Vector(1, 0, 0);
                float n = L.dot(normalRay.vector.normalized()) * 255.0 * 10;
                n = std::clamp(n, 10.0f, 255.0f);
                image[index] = n;
                image[index + 1] = n;
                image[index + 2] = n;
            } else {
                image[index] = 0;
                image[index + 1] = 0;
                image[index + 2] = 0;
            }*/
        }
    }

    // Sauvegarder l'image au format .jpg
    stbi_write_jpg("output.jpg", width, height, 3, image.data(), 100);

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    ShellExecuteA(NULL, "open", "C:\\Users\\pierr\\Downloads\\Cours\\Cpp\\RTX\\cmake-build-debug\\output.jpg", NULL, NULL, SW_SHOWDEFAULT);
    return 0;
}
