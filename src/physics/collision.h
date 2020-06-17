#pragma once

#include <iostream>
#include <vector>

#include "src/physics/body.h"

using namespace std;

namespace Physics
{

class CollisionManager {
public:
    CollisionManager(vector<Physics::Body*>* bodies) : bodies(bodies) {}

    void collide(int time_delta) {
        for (auto body_a = bodies->begin(); body_a != bodies->end(); ++body_a) {
            for (auto body_b = body_a; body_b != bodies->end(); ++body_b) {
                if (body_b != body_a && collision(*body_b, *body_a)) {
                    update_moments(*body_a, *body_b);
                }
            }
        }
    }

private:
    vector<Physics::Body*>* bodies;

    // Coefficient of resolution
    static constexpr float COR = 0.9;

    void update_moments(Physics::Body* a, Physics::Body* b) {
        Math::Vector2 new_v_a =
            (((b->get_velocity() - a->get_velocity()) * COR * b->get_mass()) +
            (a->get_velocity() * a->get_mass()) +
            (b->get_velocity() * b->get_mass())) /
            (a->get_mass() + b->get_mass());

        Math::Vector2 new_v_b =
            (((a->get_velocity() - b->get_velocity()) * COR * a->get_mass()) +
            (a->get_velocity() * a->get_mass()) +
            (b->get_velocity() * b->get_mass())) /
            (a->get_mass() + b->get_mass());

        a->set_velocity(new_v_a);
        b->set_velocity(new_v_b);
    }

    bool collision(Physics::Body* a, Physics::Body* b) {
        Math::Point com_a = a->get_center_of_mass();
        Math::Point com_b = b->get_center_of_mass();

        tuple<int, int> bb_a = a->get_bounding_box();
        tuple<int, int> bb_b = b->get_bounding_box();

        Math::Point tl_a = Math::Point(
            com_a.x - std::get<0>(bb_a) / 2,
            com_a.y - std::get<1>(bb_a) / 2
        );

        Math::Point tl_b = Math::Point(
            com_b.x - std::get<0>(bb_b) / 2,
            com_b.y - std::get<1>(bb_b) / 2
        );

        if (com_a.x + std::get<0>(bb_a) / 2 >= com_b.x - std::get<0>(bb_b) / 2 &&
            com_a.x - std::get<0>(bb_a) / 2 <= com_b.x + std::get<0>(bb_b) / 2 &&

            com_a.y + std::get<1>(bb_a) / 2 >= com_b.y - std::get<1>(bb_b) / 2 &&
            com_a.y - std::get<1>(bb_a) / 2 <= com_b.y + std::get<1>(bb_b) / 2
        ) {
            return true;
        }
        return false;
    }
};

} // namespace Physics
