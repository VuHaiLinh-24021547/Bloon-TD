#ifndef BLOON_HPP_INCLUDE
#define BLOON_HPP_INCLUDE

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#include "position.hpp"
#include "player.hpp"

class bloon
{
    public:
        bloon(vectorR2 p_pos, int p_health);
        vectorR2& getPos();
        SDL_Texture* getTex();
        SDL_Rect getBloon();
        int getHealth();

        void bloon_move();
        bool alive();
        bool bloon_reach_end();
        void bloon_pop(player& p_player);
        bool has_hit = false;

        SDL_Texture* tex;

    private:
        vectorR2 pos;
        SDL_Rect bloon_tex;
        
        int move;
        int health;
};

#endif