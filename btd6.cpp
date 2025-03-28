#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "background.hpp"
#include "bloon.hpp"
#include "position.hpp"
#include "timer.hpp"

const int window_w = 1280;
const int window_h = 720;
const int number_of_bloon = 5;

int main(int argc, char *argv[]){
    //tạo ra window và renderer
    RenderWindow window("BTD6", window_w, window_h);
    
    //tạo ra background
    SDL_Texture* background_tex = window.loadTexture("res/gfx/background.png");
    background bg(0, 0, background_tex);

    //tạo ra bloon
    SDL_Texture* red_bloon_tex = window.loadTexture("res/gfx/red_bloon.png");
    std::vector<bloon> red_bloon_v;
    
    //timer
    timer spawn_timer(100);
    int bloon_count = 15;

    //tạo ra player
    player slimebuck(100, 100);

    bool gameRunning = true;
    bool startRound = false;

    int bloon_start;
    int mouse_x, mouse_y;

    SDL_Event event;

    while(gameRunning) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
				gameRunning = false;
            
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                startRound = true;
                bloon_start = SDL_GetTicks();
            }
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a) {
                red_bloon_v[0].bloon_pop();
            }
            
        }
        window.clear();

        window.render_background(bg);
        
        window.render_health_money(slimebuck);

        spawn_timer.time_passed();
        if(bloon_count > 0 && spawn_timer.time_is_zero()) {
            bloon red_bloon(vectorR2(0.0f, 280.0f), red_bloon_tex);
            red_bloon_v.push_back(red_bloon);
            bloon_count--;
            spawn_timer.get_time_to_max();
        }
            
        for(int i=0; i<(int)red_bloon_v.size(); i++) {
            if(!red_bloon_v[i].alive()) {
                red_bloon_v.erase(red_bloon_v.begin() + i);
            }
            else {
                window.render_bloon(red_bloon_v[i]);
                red_bloon_v[i].bloon_move();
                if(red_bloon_v[i].bloon_reach_end()) {
                    slimebuck.modify_health(-1);
                    slimebuck.modify_money(1);
                }
            }
        }
    
        window.display();

        SDL_Delay(8);

    } 
    window.cleanUp();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}