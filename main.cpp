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
    return 0;
}
