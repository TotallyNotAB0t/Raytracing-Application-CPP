cmake_minimum_required(VERSION 3.25)
project(RTX)

set(CMAKE_CXX_STANDARD 17)

add_executable(RTX main.cpp CoordinatesClasses/src/Vector.cpp CoordinatesClasses/include/Vector.h CoordinatesClasses/src/Point.cpp CoordinatesClasses/include/Point.h lib/include/stb_image_write.h CoordinatesClasses/src/Ray.cpp CoordinatesClasses/include/Ray.h CoordinatesClasses/src/Matrix.cpp CoordinatesClasses/include/Matrix.h Objects/include/InstantiableObject.h Objects/src/Sphere.cpp Objects/include/Sphere.h Objects/include/ObjectUtiliy.h Objects/src/ObjectUtility.cpp Objects/src/Plane.cpp Objects/include/Plane.h)
