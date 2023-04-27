//
// Created by pierr on 26-Apr-23.
//

#ifndef RTX_POINT_H
#define RTX_POINT_H
#include <iostream>

class Point {
    private:
        float x;
        float y;
        float z;
    public:
        Point();
        Point(float x, float y, float z);
        Point operator+(Point const& p) const;
        Point operator-(Point const& p) const;
        Point operator*(Point const& p) const;
        Point operator/(Point const& p) const;
        friend std::ostream& operator<<(std::ostream& os, const Point& p);
        ~Point();
};


#endif //RTX_POINT_H
