#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "background.hpp"

background::background(int x, int y, int w, int h, SDL_Texture* tex)
    :x(x), y(y), w(w), h(h), tex(tex)
{
    size.x = 0;
    size.y = 0;
    size.w = w;
    size.h = h;

    pos.x = x;
    pos.y = y;
}   

SDL_Rect background::getBackground() {
    return size;
}

SDL_Texture* background::getTex() {
    return tex;
}

vectorR2& background::getPos() {
    return pos;
}