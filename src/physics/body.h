#pragma once

#include <vector>
#include <tuple>

#include "src/math/point.h"
#include "src/math/vector.h"
// #include "src/physics/force.h"

using namespace std;

namespace Physics {

class Body {
public:
    Body(
        float mass,
        Math::Point center_of_mass,
        tuple<int, int> bounding_box = {0, 0},
        bool stationary = false
    ) :
        mass(mass),
        center_of_mass(center_of_mass),
        bounding_box(bounding_box),
        stationary(stationary) {};

    virtual void tick(int time_delta);
    virtual void add_force(Math::Vector2 force);

    float get_mass() const { return mass; }
    Math::Point get_center_of_mass() const { return center_of_mass; }
    tuple<int, int> get_bounding_box() const { return bounding_box; }
    Math::Vector2 get_velocity() const { return velocity; }
    void set_velocity(Math::Vector2 v) { this->velocity = v; }

    Math::Vector2 sum_forces() const;
protected:
    float mass;
    Math::Point center_of_mass;
    bool stationary;
    tuple<int, int> bounding_box;

    Math::Vector2 acceleration;
    Math::Vector2 velocity;

    vector<Math::Vector2> forces;
};

}