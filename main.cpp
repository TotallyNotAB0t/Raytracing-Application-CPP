#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <vector>
#include "lib/include/stb_image_write.h"
#include "Objects/include/InstantiableObject.h"
#include "CoordinatesClasses/include/Vector.h"
#include "CoordinatesClasses/include/Point.h"
#include "Objects/include/ObjectUtiliy.h"
#include "Objects/include/Sphere.h"
#include "Objects/include/Plane.h"

int main() {
    Vector test(1, 2, 3);
    Vector testt = test + test;
    std::cout << testt << std::endl;
    Vector testtt = testt - test;
    std::cout << testtt << std::endl;
    Point p(2,2,6.5);
    std::cout << p << std::endl;
    std::cout << test[2] << std::endl;
    std::string testtttt;

    // Image test setup
    int width = 1920;  // Width of the image
    int height = 1080; // Height of the image
    int channels = 3; // Number of channels (RGB)

    unsigned char* image_data = new unsigned char[width * height * channels];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            image_data[index] = x;     // Red channel
            image_data[index + 1] = y;   // Green channel
            image_data[index + 2] = 0;   // Blue channel
        }
    }

    stbi_write_jpg("output.jpg", width, height, channels, image_data, 100);

    delete[] image_data;

    // Object creation test
    std::string filename = "test_objects.txt";
    std::vector<InstantiableObject*> objects = ObjectUtility::createObjectsFromFile(filename);

    for(const auto& obj : objects){
        if (Sphere* sphere = dynamic_cast<Sphere*>(obj)) {
            std::cout << "Sphere position: (" << sphere->position[0] << ", "
                      << sphere->position[1] << ", " << sphere->position[2] << ")" << std::endl;
        }
        if (Plane* plane = dynamic_cast<Plane*>(obj)){
            std::cout << "Plane position width " << plane->width << " height : " << plane->height << " position : "
            << plane->position[0] << " " << plane->position[1] << " " << plane->position[2] << std::endl;
        }
    }

    return 0;
}
