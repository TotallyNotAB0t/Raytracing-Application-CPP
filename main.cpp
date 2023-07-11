#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <vector>
#include "lib/include/stb_image_write.h"
#include "Objects/include/InstantiableObject.h"
#include "Classes/Coordinates/include/Matrix.h"
#include "Classes/include/Scene.h"
#include "Classes/Entities/include/Object.h"
#include "Classes/Entities/include/Camera.h"
#include "Classes/Entities/include/Sphere.h"
#include "Classes/Entities/include/Carre.h"
#include "Classes/Entities/include/Cube.h"
#include <algorithm>

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
    /*Matrix mat = Matrix();
    mat(0, 0) = 1;
    mat(0, 1) = 1;
    mat(0, 2) = 1;
    mat(1, 0) = 1;
    mat(1, 1) = 2;
    mat(1, 2) = 3;
    mat(2, 0) = 2;
    mat(2, 1) = 4;
    mat(2, 2) = 5;

    std::cout << mat << std::endl;

    HPoint hp = HPoint(1, 2, 3, 1);
    std::cout << mat * hp << std::endl;
    return 0;*/

/*    HPoint yeet = mat * hp;
    if (Matrix::INV(mat, inv)){
        std::cout << inv << std::endl;
    }*/

    Matrix mat = Matrix();
    std::cout << mat << std::endl;

    // Image test setup
/*    int width = 1920;
    int height = 1080;
    int channels = 3;

    unsigned char *image_data = new unsigned char[width * height * channels];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            image_data[index] = x;
            image_data[index + 1] = y;
            image_data[index + 2] = 0;
        }
    }

    stbi_write_jpg("output.jpg", width, height, channels, image_data, 100);

    delete[] image_data;*/

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
    scene.setAmbiant(Color(0.1, 0.1, 0.1));

    // Ajouter des objets à la scène
    Material mat1(Color(0.2, 0.2, 0.8), Color(0.8, 0.8, 0.8), Color(1.0, 1.0, 1.0), 50);
    //Material mat2(Color(0.2, 0.8, 0.8), Color(0.8, 0.8, 0.8), Color(1.0, 1.0, 1.0), 20);
    Sphere* sphere1 = new Sphere(mat1);
    sphere1->translate(1, 0, 5);

    Cube* sphere2 = new Cube();
    sphere2->translate(-1, 0, 5);

    scene.addObject(sphere1);
    //scene.addObject(sphere2);
    std::cout << sphere1->trans << std::endl;

    //Carre* carre1 = new Carre();

/*

    Material mat2(Color(0.8, 0.2, 0.2), Color(0.8, 0.8, 0.8), Color(1.0, 1.0, 1.0), 50);
    Cube* cube1 = new Cube(Point(-2, 0, -5), 1, mat2);
    scene.addObject(cube1);
*/

    // Ajouter une lumière à la scène
/*    Light* light1 = new Light(Point(0, 5, 0), Color(1.0, 1.0, 1.0), Color(1.0, 1.0, 1.0));
    scene.addLight(light1);*/

    // Créer la caméra
    Camera camera(5);
    camera.translate(0, 0, -20);

    // Rendu de l'image
    int width = 800;
    int height = 600;
    std::vector<unsigned char> image(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float u = float(x) / float(width);
            float v = float(y) / float(height);
            Ray ray = camera.getRay(u, v,  (float)width/(float)height);

            int index = (y * width + x) * 3;
            bool isIntersect = false;
            Point ptrPoint;
            //isIntersect = scene.renderScene(ray, ptrPoint);
            //isIntersect = sphere1->intersect(ray, ptrPoint);
            Color colorToPrint = scene.renderScene(ray, ptrPoint);
            image[index] = colorToPrint[0] * 255.0f;
            image[index + 1] = colorToPrint[1] * 255.0f;
            image[index + 2] = colorToPrint[2] * 255.0f;

            Ray normalRay = sphere2->getNormal(ptrPoint, Point());
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

    return 0;
}
