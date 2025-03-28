#ifndef BLOON_HPP_INCLUDE
#define BLOON_HPP_INCLUDE

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "position.hpp"

class bloon
{
    public:
        bloon(vectorR2 p_pos, SDL_Texture* p_tex);
        vectorR2& getPos();
        SDL_Texture* getTex();
        SDL_Rect getBloon();
        void bloon_move();
        bool alive();
        bool bloon_reach_end();
        void bloon_pop();
    private:
        vectorR2 pos;
        SDL_Rect bloon_tex;
        SDL_Texture* tex;
        int move;
        int health = 1;
};

#endif