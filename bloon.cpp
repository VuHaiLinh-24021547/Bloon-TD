#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#include "bloon.hpp"
#include "position.hpp"
#include "player.hpp"

const int bloon_w = 32;
const int bloon_h = 40;

bloon::bloon(vectorR2 p_pos, int p_health)
:pos(p_pos) {
    bloon_tex.x = 0;
    bloon_tex.y = 0;
    bloon_tex.w = bloon_w;
    bloon_tex.h = bloon_h;

    move = 1;

    health = p_health;
}


vectorR2& bloon::getPos() {
    return pos;
}

SDL_Texture* bloon::getTex() {
    return tex;
}

SDL_Rect bloon::getBloon() {
    return bloon_tex;
}

bool bloon::alive() {
    if(health <= 0) return false;
    return true;
}

bool bloon::bloon_reach_end() {
    if(pos.y >= 720.0f) {
        health = 0;
        return true;
    }
    return false;
}

int bloon::getHealth() {
    return health;
}

void bloon::bloon_pop(player& p_player) {
    health--;
    p_player.modify_money(1);
}
void bloon::bloon_move() {
    if(move == 1) {
        if(pos.x < 610.0f && pos.y == 280.0f) {
            pos.x ++;
        }
        
        else if(pos.x == 610.0f && pos.y > 115.0f) {
            pos.y --;
        }

        else if(pos.x > 410.0f && pos.y == 115.0f) {
            pos.x --;
        }
        
        else if(pos.x == 410.0f && pos.y == 115.0f) {
            move = 2;
        }
    }

    if(move == 2) {
        if(pos.x == 410.0f && pos.y < 550.0f) {
            pos.y ++;
        }
        
        else if(pos.x > 200.0f && pos.y == 550.0f) {
            pos.x--;
        }

        else if(pos.x == 200.0f && pos.y > 400.0f) {
            pos.y--;
        }

        else if(pos.x == 200.0f && pos.y == 400.0f) {
            move = 3;
        }
    }

    if(move == 3) {
        if(pos.x < 760.0f && pos.y == 400.0f) {
            pos.x++;
        }

        else if(pos.x < 800.0f && pos.y > 225.0f) {
            pos.x++;
            pos.y--;
        }

        else if(pos.x == 800.0f && pos.y > 215.0f) {
            pos.y--;
        }

        else if(pos.x < 935.0f && pos.y == 215.0f) {
            pos.x++;
        }

        else if(pos.x == 935.0f && pos.y < 500.0f) {
            pos.y++;
        }

        else if(pos.x == 935.0f && pos.y == 500.0f) {
            move = 4;
        } 
    }

    if(move == 4) {
        if(pos.x > 550.0f && pos.y == 500.0f) {
            pos.x--;
        }

        else if(pos.x == 550.0f && pos.y < 720.0f) {
            pos.y++;
        }
    }
}