#ifndef RTX_COLOR_H
#define RTX_COLOR_H
#include <iostream>

class Color 
{
public:
    Color();
    Color(const Color& color);
    Color(float r, float g, float b);
    ~Color();

    float operator[](int index) const;
    float& operator[](int index);

    Color operator+(const Color& c) const;
    Color operator-(const Color& c) const;
    Color operator*(const Color& c) const;
    Color operator*(float f) const;
    Color operator/(float f) const;

    Color& operator+=(const Color& c);
    Color& operator-=(const Color& c);
    Color& operator*=(const Color& c);
    Color& operator*=(float f);
    Color& operator/=(float f);

    Color mul(const Color& c) const;
    Color mul(const float c) const;

private:
    float r, g, b;


};

#endif //RTX_COLOR_H
