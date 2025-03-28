#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "background.hpp"

const int background_w = 1280;
const int background_h = 720;

background::background(int x, int y, SDL_Texture* tex)
    :x(x), y(y), tex(tex)
{
    size.x = x;
    size.y = y;
    size.w = background_w;
    size.h = background_h;
}   

SDL_Rect background::getBackground() {
    return size;
}

SDL_Texture* background::getTex() {
    return tex;
}