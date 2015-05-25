#ifndef COMPARATOR_HPP
#define CAMPARATOR_HPP


#include <SDL2/SDL.h>

static bool compare_SDL_Color(SDL_Color* p1, SDL_Color* p2) {
     return p1->r == p2->r &&
            p1->g == p2->g &&
            p1->b == p2->b &&
            p1->a == p2->g;
}

static bool compare_SDL_Color(SDL_Color p1, SDL_Color p2) {
    return p1.r == p2.r &&
            p1.g == p2.g &&
            p1.b == p2.b &&
            p1.a == p2.g;
}

#endif