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
	roundStr = std::to_string(round);

	healthSurface = TTF_RenderText_Blended( gFont, healthStr.c_str(), {0, 0, 0, 255});
	moneySurface = TTF_RenderText_Blended( gFont, moneyStr.c_str(), {0, 0, 0, 255});
	roundSurface = TTF_RenderText_Blended( gFont, roundStr.c_str(), {0, 0, 0, 255});

    if( healthSurface == NULL || moneySurface == NULL || roundSurface == NULL)
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
	else {
		textureHealth = SDL_CreateTextureFromSurface(renderer, healthSurface);
		textureMoney = SDL_CreateTextureFromSurface(renderer, moneySurface);
		textureRound = SDL_CreateTextureFromSurface(renderer, roundSurface);

		if(textureHealth == NULL || textureMoney == NULL || textureRound == NULL) {
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

SDL_Texture* player::getRoundTex() {
	return textureRound;
}