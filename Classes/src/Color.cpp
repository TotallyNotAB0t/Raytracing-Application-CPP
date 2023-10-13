#include "Color.h"

Color::Color()
{
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
}

Color::Color(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::~Color() {}

float Color::operator[](int index) const
{
    switch (index)
    {
        case 0:
            return r;
        case 1:
            return g;
        case 2:
            return b;
        default:
            throw std::out_of_range("Color index out of range.");
    }
}

float& Color::operator[](int index)
{
    switch (index)
    {
        case 0:
            return r;
        case 1:
            return g;
        case 2:
            return b;
        default:
            throw std::out_of_range("Color index out of range.");
    }
}

Color Color::operator+(const Color& c) const
{
    return Color(r + c.r, g + c.g, b + c.b);
}

Color Color::operator-(const Color& c) const
{
    return Color(r - c.r, g - c.g, b - c.b);
}

Color Color::operator*(const Color& c) const
{
    return Color(r * c.r, g * c.g, b * c.b);
}

Color Color::operator*(float f) const
{
    return Color(r * f, g * f, b * f);
}

Color Color::operator/(float f) const
{
    return Color(r / f, g / f, b / f);
}

Color& Color::operator+=(const Color& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}

Color& Color::operator-=(const Color& c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    return *this;
}

Color& Color::operator*=(const Color& c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    return *this;
}

Color& Color::operator*=(float f)
{
    r *= f;
    g *= f;
    b *= f;
    return *this;
}

Color& Color::operator/=(float f)
{
    r /= f;
    g /= f;
    b /= f;
    return *this;
}

Color Color::mul(const Color& c) const
{
    return Color(r * c.r, g * c.g, b * c.b);
}
Color Color::mul(const float c) const
{
    return Color(r * c, g * c, b * c);
}

Color::Color(const Color &color) {
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
}
