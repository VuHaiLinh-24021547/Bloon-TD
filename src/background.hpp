#ifndef BACKGROUND_HPP_INCLUDE
#define BACKGROUND_HPP_INCLUDE

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class background
{
    public:
        background(int x, int y, SDL_Texture* tex);

        SDL_Rect getBackground();
        SDL_Texture* getTex();

    private:
        int x, y;
        SDL_Rect size;
        SDL_Texture* tex;
};

#endif