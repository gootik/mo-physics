#pragma once

#include <tuple>

#include "src/physics/body.h"
#include "src/rendering/renderable.h"

namespace Entity
{
class Ground : public Physics::Body, public Render::Renderable {
public:
    Ground(Math::Point center = Math::Point(0, 450)) : Physics::Body(900, center, {1000, 50}, true) {}

    virtual void draw(SDL_Window*, SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_Rect r = {(int)center_of_mass.x - 500, (int)center_of_mass.y - 25, 2000, 2000};
        SDL_RenderFillRect(renderer, &r);
    }
};

} // namespace Entity
