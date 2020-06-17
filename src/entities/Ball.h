#pragma once

#include "src/physics/body.h"
#include "src/math/point.h"

#include "src/rendering/renderable.h"

namespace Entity
{

class Ball : public Physics::Body , public Render::Renderable {
public:
    Ball(float mass = 2.5, Math::Point initial_position = Math::Point(60, 10)) :
        Physics::Body(mass, initial_position, {50, 50}) {
    };

    virtual void pre_tick_draw(SDL_Window* window, SDL_Renderer* renderer) {

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        for (auto& f: forces) {
            Math::Vector2 end = ((f * 50) + Math::Vector2(center_of_mass.x, center_of_mass.y));
            SDL_RenderDrawLine(renderer, (int)this->center_of_mass.x, (int)this->center_of_mass.y, (int)end.x, (int)end.y);
        }
    }

    virtual void draw(SDL_Window* window, SDL_Renderer* renderer) {
        rect = {(int)this->center_of_mass.x - (50/2), (int)this->center_of_mass.y - (50/2), 50, 50};

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect);

        // DEBUGGING
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        Math::Vector2 end = ((velocity * 10) + Math::Vector2(center_of_mass.x, center_of_mass.y));
        SDL_RenderDrawLine(renderer, (int)this->center_of_mass.x, (int)this->center_of_mass.y, (int)end.x, (int)end.y);
    }

    void add_point_mass(float m) {
        this->mass += m;
    }

private:
    int radius;
    SDL_Rect rect;
};

} // namespace Entity
