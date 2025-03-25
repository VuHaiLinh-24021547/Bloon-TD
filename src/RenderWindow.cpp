#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#include "RenderWindow.hpp"
#include "background.hpp"
#include "player.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
	}

	if (TTF_Init() == -1) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
    }
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
}

SDL_Texture* RenderWindow::loadTexture(const char* path) {
	SDL_Texture* tex = IMG_LoadTexture(renderer, path);
	if(tex == NULL) {
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}
	return tex;
}

void RenderWindow::render_background(background &p_background) {
	SDL_Rect src;
	src.x = p_background.getBackground().x;
	src.y = p_background.getBackground().y;
	src.w = p_background.getBackground().w;
	src.h = p_background.getBackground().h;

	SDL_Rect dst;
	dst.x = p_background.getBackground().x;
	dst.y = p_background.getBackground().y;
	dst.w = p_background.getBackground().w;
	dst.h = p_background.getBackground().h;
	SDL_RenderCopy(renderer, p_background.getTex(), &src, &dst);
}

void RenderWindow::render_health_money(player &p_player) {
	p_player.create_texture(renderer);
	
	SDL_Rect health_size;
	health_size.x = 200;
	health_size.y = 0;
	health_size.w = 50;
	health_size.h = 30;

    SDL_Rect money_size;
	money_size.x = 500;
	money_size.y = 0;
	money_size.w = 50;
	money_size.h = 30;

	SDL_RenderCopy(renderer, p_player.getHealthTex(), NULL, &health_size);
	SDL_RenderCopy(renderer, p_player.getMoneyTex(), NULL, &money_size);
}

void RenderWindow::render_bloon(bloon &p_bloon) {
	SDL_Rect src;
	src.x = p_bloon.getBloon().x;
	src.y = p_bloon.getBloon().y;
	src.w = p_bloon.getBloon().w;
	src.h = p_bloon.getBloon().h;

	SDL_Rect dst;
	dst.x = p_bloon.getPos().x;
	dst.y = p_bloon.getPos().y;
	dst.w = p_bloon.getBloon().w;
	dst.h = p_bloon.getBloon().h;
	SDL_RenderCopy(renderer, p_bloon.getTex(), &src, &dst);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}