#include "src/physics/body.h"

#include <iostream>

namespace Physics
{

void Body::tick(int time_delta) {
    if (stationary) {
        return;
    }

    Math::Vector2 summed_forces = sum_forces();
    Math::Vector2 friction = summed_forces * -1 * 0.05;
    summed_forces = summed_forces + friction;

    acceleration = summed_forces / mass;

    velocity = velocity + (acceleration * time_delta);

    // Update new center_of_mass
    Math::Vector2 p_delta = (velocity * time_delta) * 0.8;
    center_of_mass += p_delta;

    forces.clear();
}

Math::Vector2 Body::sum_forces() const {
    Math::Vector2 summed_forces;
    for (auto& f : forces) {
        summed_forces = summed_forces + f;
    }

    return summed_forces;
}

void Body::add_force(Math::Vector2 force) {

    // Cant move stationary objects!
    if (stationary) {
        return;
    }

    forces.push_back(force);
}

} // namespace Physics
