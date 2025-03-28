#ifndef RENDERWINDOW_HPP_INCLUDE
#define RENDERWINDOW_HPP_INCLUDE

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#include "background.hpp"
#include "bloon.hpp"
#include "player.hpp"

class RenderWindow {
    public:
        RenderWindow(const char* p_title, int p_w, int p_h);

        SDL_Texture* loadTexture(const char* path);
        
        void render_background(background &p_background);
        void render_bloon(bloon &p_bloon);
        void render_health_money(player &p_player);

        void clear();
        void cleanUp();
        void display();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

};

#endif