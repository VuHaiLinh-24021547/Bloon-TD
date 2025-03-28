#ifndef PLAYER_HPP_INCLUDE
#define PLAYER_HPP_INCLUDE

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <cstdint> 

class player
{
    public:
        int health;
        int money;

        player(int init_health, int init_money)
        :health(init_health), money(init_money) {}

        void modify_health(int amount) {
            health += amount;
        }

        void modify_money(int amount) {
            money += amount;
        }

        void create_texture(SDL_Renderer* renderer);
        SDL_Texture* getHealthTex();
        SDL_Texture* getMoneyTex();

    private:
        TTF_Font* gFont = TTF_OpenFont("fonts/Crashnumberinggothic-MAjp.ttf", 30);

        std::string healthStr;
        std::string moneyStr;

        SDL_Surface* healthSurface;
        SDL_Surface* moneySurface;

        SDL_Texture* textureHealth;
        SDL_Texture* textureMoney;
};

#endif