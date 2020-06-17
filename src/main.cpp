#include <iostream>
#include <vector>

#include "SDL.h"
#include "constants.h"

#include "src/math/point.h"

#include "src/physics/body.h"
#include "src/physics/collision.h"

#include "src/entities/Ball.h"
#include "src/entities/Ground.h"

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Surface* surface = nullptr;

bool quiting = false;

Entity::Ball* ball = new Entity::Ball(2.5);
Entity::Ground* ground = new Entity::Ground();

vector<Physics::Body*> physics_bodies = {};
vector<Render::Renderable*> renderables = {};


Physics::CollisionManager* collision_manager = new Physics::CollisionManager(&physics_bodies);

int terminate_with_error() {
    cout << "ERROR " << SDL_GetError() << endl;
    SDL_Quit();

    return 1;
}

void loop() {
    SDL_Event e;
    while (!quiting){
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){
                quiting = true;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP){
                ball->add_force(Math::Vector2(0, -0.5) * ball->get_mass());
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN){
                ball->add_force(Math::Vector2(0, 0.5) * ball->get_mass());
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){
                ball->add_force(Math::Vector2(0.5, 0) * ball->get_mass());
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT) {
                ball->add_force(Math::Vector2(-0.5, 0) * ball->get_mass());
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w) {
                ball->add_point_mass(1);
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q){
                quiting = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        collision_manager->collide(1);

        // Anything to draw before running physics
        for (auto r : renderables) {
            r->pre_tick_draw(window, renderer);
        }

        // Physics.
        for (auto b : physics_bodies) {
            // calculate new values
            // Gravity!
            // b->add_force(Math::Vector2(0, 0.098) * b->get_mass());

            b->tick(1);
        }

        for (auto r : renderables) {
            r->draw(window, renderer);
        }

        SDL_RenderPresent(renderer);
    }
}


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return terminate_with_error();
    }

    window = SDL_CreateWindow("Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        return terminate_with_error();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
	    SDL_DestroyWindow(window);
	    return terminate_with_error();
    }

    physics_bodies.push_back(static_cast<Physics::Body*>(ball));
    physics_bodies.push_back(static_cast<Physics::Body*>(ground));

    renderables.push_back(static_cast<Render::Renderable*>(ball));
    renderables.push_back(static_cast<Render::Renderable*>(ground));

    loop();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
