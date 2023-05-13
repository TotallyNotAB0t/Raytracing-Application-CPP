//
// Created by pierr on 26-Apr-23.
//

#ifndef RTX_VECTOR_H
#define RTX_VECTOR_H
#include <cmath>
#include <iostream>

class Vector {
    private:
        float x;
        float y;
        float z;
    public:
        Vector();
        Vector(float x, float y, float z);
        Vector(const Vector& v);

        Vector& operator=(const Vector& v);
        Vector(Vector&& v) noexcept;
        Vector& operator=(Vector&& v) noexcept;

        float operator[](int val) const;
        float& operator[](int val);

        float norm() const;
        Vector normalized() const;
        float dot(const Vector& v) const;

        Vector operator-() const;
        Vector operator+(Vector const& v) const;
        Vector operator-(Vector const& v) const;
        Vector operator*(float val) const;
        Vector operator/(float val) const;

        friend std::ostream& operator<<(std::ostream& os, const Vector& v);

        ~Vector();
};

#endif //RTX_VECTOR_H
