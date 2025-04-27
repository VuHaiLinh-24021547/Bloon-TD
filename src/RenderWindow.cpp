#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#include "RenderWindow.hpp"
#include "background.hpp"
#include "player.hpp"
#include "projectile.hpp"

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

SDL_Renderer* RenderWindow::getrenderer() {
	return renderer;
}

void RenderWindow::render_background(background &p_background) {
	SDL_Rect src;
	src.x = p_background.getBackground().x;
	src.y = p_background.getBackground().y;
	src.w = p_background.getBackground().w;
	src.h = p_background.getBackground().h;

	SDL_Rect dst;
	dst.x = p_background.getPos().x;
	dst.y = p_background.getPos().y;
	dst.w = p_background.getBackground().w;
	dst.h = p_background.getBackground().h;
	SDL_RenderCopy(renderer, p_background.getTex(), &src, &dst);
}

void RenderWindow::render_status(player &p_player) {
	p_player.create_texture(renderer);
	
	SDL_Rect health_size;
	health_size.x = 1150;
	health_size.y = 92;
	SDL_QueryTexture(p_player.getHealthTex(), NULL, NULL, &health_size.w, &health_size.h);

    SDL_Rect money_size;
	money_size.x = 1150;
	money_size.y = 148;
	SDL_QueryTexture(p_player.getMoneyTex(), NULL, NULL, &money_size.w, &money_size.h);

	SDL_Rect round_size;
	round_size.x = 1150;
	round_size.y = 200;
	SDL_QueryTexture(p_player.getRoundTex(), NULL, NULL, &round_size.w, &round_size.h);

	SDL_RenderCopy(renderer, p_player.getHealthTex(), NULL, &health_size);
	SDL_RenderCopy(renderer, p_player.getMoneyTex(), NULL, &money_size);
	SDL_RenderCopy(renderer, p_player.getRoundTex(), NULL, &round_size);
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

void RenderWindow::render_monkey(monkey &p_monkey) {
	SDL_Rect src;
	src.x = p_monkey.getMonkey().x;
	src.y = p_monkey.getMonkey().y;
	src.w = p_monkey.getMonkey().w;
	src.h = p_monkey.getMonkey().h;

	SDL_Rect dst;
	dst.x = p_monkey.getPos().x;
	dst.y = p_monkey.getPos().y;
	dst.w = p_monkey.getMonkey().w;
	dst.h = p_monkey.getMonkey().h;
	SDL_RenderCopy(renderer, p_monkey.getTex(), &src, &dst);
}

void RenderWindow::render_dart(projectile &p_dart) {
	SDL_Rect src;
	src.x = p_dart.getDart().x;
	src.y = p_dart.getDart().y;
	src.w = p_dart.getDart().w;
	src.h = p_dart.getDart().h;

	SDL_Rect dst;
	dst.x = p_dart.getPos().x;
	dst.y = p_dart.getPos().y;
	dst.w = p_dart.getDart().w;
	dst.h = p_dart.getDart().h;

	SDL_RenderCopy(renderer, p_dart.getTex(), &src, &dst);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}