#pragma once

#include <string>

#include "src/math/vector.h"

namespace Math
{

class Point {
public:
    Point(float x, float y) : x(x), y(y) {};

    Point& operator +=(const Point& b) {
        this->x += b.x;
        this->y += b.y;

        return *this;
    }

    Point& operator +=(const Vector2& b) {
        this->x += b.x;
        this->y += b.y;

        return *this;
    }

    std::string to_string() {
        return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
    }


    float x;
    float y;
};

} // namespace Math
