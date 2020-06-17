#pragma once

#include "SDL.h"

namespace Render
{

class Renderable {
public:
    virtual void pre_tick_draw(SDL_Window*, SDL_Renderer*) {};
    virtual void draw(SDL_Window*, SDL_Renderer*) = 0;
};

} // namespace Render
