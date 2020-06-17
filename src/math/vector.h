#pragma once

#include <cmath>
#include <string>

namespace Math
{

class Vector2
{
public:
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    ~Vector2() = default;

    void normalize() {
        float len = length();
        x = x / len;
        y = y / len;
    }

    float length() {
        return sqrt((x*x) + (y*y));
    }

    Vector2 operator +(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 operator -(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 operator *(const Vector2& v) const {
        return Vector2(x * v.x, y * v.y);
    }

    Vector2 operator *(const float s) const {
        return Vector2(x * s, y * s);
    }

    Vector2 operator /(const float s) const {
        return Vector2(x / s, y / s);
    }

    Vector2& operator +=(const Vector2& v) {
        this->x += v.x;
        this->y += v.y;

        return *this;
    }

    std::string to_string() {
        return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
    }


    /*
        Vector2 math...
    */

    float x;
    float y;
};

} // namespace Math
