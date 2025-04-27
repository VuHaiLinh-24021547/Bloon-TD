#ifndef BACKGROUND_HPP_INCLUDE
#define BACKGROUND_HPP_INCLUDE

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "position.hpp"

class background
{
    public:
        background(int x, int y, int w, int h, SDL_Texture* tex);

        SDL_Rect getBackground();
        SDL_Texture* getTex();
        vectorR2& getPos();

    private:
        int x, y, w, h;
        SDL_Rect size;
        SDL_Texture* tex;
        vectorR2 pos;
};

#endif