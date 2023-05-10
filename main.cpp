#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include "Vector.h"
#include "Point.h"

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

    return 0;
}
