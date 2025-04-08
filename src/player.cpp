#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <cstdint> 

#include "player.hpp"

void player::create_texture(SDL_Renderer* renderer) {
	if(!gFont) {
		std::cout<< "Font failed to load. " << TTF_GetError() << std::endl;
	}
        
	healthStr = std::to_string(health);
	moneyStr = std::to_string(money);

	healthSurface = TTF_RenderText_Blended( gFont, healthStr.c_str(), {255, 255, 255, 255});
	moneySurface = TTF_RenderText_Blended( gFont, moneyStr.c_str(), {255, 255, 255, 255});

    if( healthSurface == NULL || moneySurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
	else {
		textureHealth = SDL_CreateTextureFromSurface(renderer, healthSurface);
		textureMoney = SDL_CreateTextureFromSurface(renderer, moneySurface);

		if(textureHealth == NULL || textureMoney == NULL) {
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
	}
}

SDL_Texture* player::getHealthTex() {
    return textureHealth;
}

SDL_Texture* player::getMoneyTex() {
    return textureMoney;
}