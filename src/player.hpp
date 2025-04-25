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
        int round;

        player(int init_health, int init_money, int init_round)
        :health(init_health), money(init_money), round(init_round) {}

        void modify_health(int amount) {
            health += amount;
        }

        void modify_money(int amount) {
            money += amount;
        }

        void modify_round() {
            round++;
        }

        void create_texture(SDL_Renderer* renderer);
        SDL_Texture* getHealthTex();
        SDL_Texture* getMoneyTex();
        SDL_Texture* getRoundTex();

    private:
        TTF_Font* gFont = TTF_OpenFont("fonts/Crashnumberinggothic-MAjp.ttf", 30);

        std::string healthStr;
        std::string moneyStr;
        std::string roundStr;

        SDL_Surface* healthSurface;
        SDL_Surface* moneySurface;
        SDL_Surface* roundSurface;

        SDL_Texture* textureHealth;
        SDL_Texture* textureMoney;
        SDL_Texture* textureRound;
};

#endif