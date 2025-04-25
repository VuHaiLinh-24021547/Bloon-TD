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
#include "projectile.hpp"

class monkey
{
    public:
        monkey(vectorR2 p_pos, SDL_Texture* p_tex);
        SDL_Texture* getTex();
        SDL_Rect getMonkey();
        vectorR2& getPos();
        bool valid_place(const int &x, const int &y);
        void update_target(std::vector<bloon> &bloon_v);
        bool shoot(player &p_player);   
        bloon* target = nullptr;
        int getRange();
        std::vector<projectile> dart_v;

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