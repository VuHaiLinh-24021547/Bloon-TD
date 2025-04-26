#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "monkey.hpp"
#include "position.hpp"
#include "player.hpp"
#include "bloon.hpp"
#include "projectile.hpp"


const int monkey_w = 60;
const int monkey_h = 60;

monkey::monkey(vectorR2 p_pos, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
    monkey_tex.x = 0;
    monkey_tex.y = 0;
    monkey_tex.w = monkey_w;
    monkey_tex.h = monkey_h;
}

SDL_Texture* monkey::getTex() {
    return tex;
}

SDL_Rect monkey::getMonkey() {
    return monkey_tex;
}

vectorR2& monkey::getPos() {
    return pos;
}

void monkey::update_target(std::vector<bloon>& bloon_v) {
    bloon* closest = nullptr;
    float closest_distance_square = range*range;

    for(bloon &p_bloon : bloon_v) {
        if(!p_bloon.alive()) continue;

        float dx = p_bloon.getPos().x - pos.x;
        float dy = p_bloon.getPos().y - pos.y;
        float distance_square = dx*dx + dy*dy;

        if(distance_square <= closest_distance_square) {
            closest_distance_square = distance_square;
            closest = &p_bloon;
        }
    }

    target = closest;
}

void monkey::move(const int &x, const int &y) {
    pos.x = x;
    pos.y = y;
}

int monkey::getRange() {
    return range;
}

bool monkey::shoot(player& p_player) {
    time_since_last_shot++;

    if(target && target->alive()) {
        float dx = target->getPos().x - pos.x;
        float dy = target->getPos().y - pos.y;
        float distance_square = dx*dx + dy*dy;

        if(distance_square <= range*range) {
            if(time_since_last_shot >= fire_cooldown) {
                time_since_last_shot = 0;

                // target->bloon_pop(p_player);

                if(!target->alive()) {
                    target = nullptr;
                }
                return true;
            }
            else return false;
        }
        else {
            target = nullptr;
        }
    }
    else {
        target = nullptr;
    }
    return false;
}

