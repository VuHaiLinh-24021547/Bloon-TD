#ifndef MONKEY_HPP_INCLUDE
#define MONYKEY_HPP_INCLUDE

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "position.hpp"
#include "player.hpp"
#include "bloon.hpp"

class monkey
{
    public:
        monkey(vectorR2 p_pos, SDL_Texture* p_tex);
        SDL_Texture* getTex();
        SDL_Rect getMonkey();
        vectorR2& getPos();
        bool valid_place(const int &x, const int &y);
        void update_target(std::vector<bloon> &bloon_v);
        void shoot(player &p_player);
        bloon* target = nullptr;
    private:
        vectorR2 pos;
        SDL_Texture* tex;
        SDL_Rect monkey_tex;
        float range = 100.0f;
        int cost = 50;
        int damage;
        int fire_cooldown = 100;
        int time_since_last_shot = 1000;

};

#endif