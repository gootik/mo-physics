#pragma once

#include "src/math/point.h"
#include "src/math/vector.h"

namespace Physics
{

class Force : public Vector2 {
public:
    Force(int magnitude, Math::Point direction) :
        Vector2(direction.x * magnitude, direction.y * magnitude),
        magnitude(magnitude),
        direction(direction)
    {

    }

private:
    int magnitude;
    Math::Point direction;
}

} // namespace Physics
