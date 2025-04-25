#ifndef PROJECTILE_HPP_INCLUDE
#define PROJECTILE_HPP_INCLUDE

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "position.hpp"
#include "bloon.hpp"

class projectile{
    public:
        projectile(vectorR2 p_pos, SDL_Texture* p_tex, vectorR2 target_pos);
        SDL_Texture* getTex();
        SDL_Rect getDart();
        vectorR2 &getPos();
        void move();
        void pop();
        bool destroy();
    private:
        vectorR2 pos;
        SDL_Texture* tex;
        SDL_Rect dart_tex;
        vectorR2 direction;
        int pierce = 2;

};

#endif