#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "projectile.hpp"
#include "position.hpp"
#include "bloon.hpp"

const int dart_w = 20;
const int dart_h = 16;

projectile::projectile(vectorR2 p_pos, SDL_Texture* p_tex, vectorR2 target_pos)
:pos(p_pos), tex(p_tex) {
    dart_tex.x = 0;
    dart_tex.y = 0;
    dart_tex.w = dart_w;
    dart_tex.h = dart_h;
    
    direction.x = (target_pos.x+16) - (pos.x+dart_w/2);
    direction.y = (target_pos.y+20) - (pos.y+dart_h/2);
}

SDL_Texture* projectile::getTex() {
    return tex;
}

SDL_Rect projectile::getDart() {
    return dart_tex;
}

vectorR2 &projectile::getPos() {
    return pos;
}

void projectile::pop() {
    pierce--;
}

bool projectile::destroy() {
    return(pierce==0);
}

void projectile::move() {
    pos.x += direction.x/20;
    pos.y += direction.y/20;
}