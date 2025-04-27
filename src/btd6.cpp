#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <map>

#include "RenderWindow.hpp"
#include "background.hpp"
#include "bloon.hpp"
#include "position.hpp"
#include "timer.hpp"
#include "monkey.hpp"
#include "projectile.hpp"
#include "music.hpp"

const int window_w = 1280;
const int window_h = 720;

void create_bloon(int &amount, int limit, std::vector<bloon> &bloon_v, timer &spawn_timer, const int &bloon_type) {
    if(amount > limit && spawn_timer.time_is_zero()) {
        bloon bloons(vectorR2(0.0f, 280.0f), bloon_type);
        bloon_v.push_back(bloons);
        amount--;
        spawn_timer.get_time_to_max();
    }
}

int main(int argc, char *argv[]){
    //tạo ra window và renderer
    RenderWindow window("BTD6", window_w, window_h);
    
    //tạo ra background
    SDL_Texture* background_tex = window.loadTexture("res/gfx/background.png");
    background bg(0, 0, 1280, 720, background_tex);

    SDL_Texture* start_background_tex = window.loadTexture("res/gfx/start_background.png");
    background start_bg(0, 0, 1280, 720, start_background_tex);

    SDL_Texture* end_screen_tex = window.loadTexture("res/gfx/end_screen.png");
    background end_screen(150, 400, 500, 121, end_screen_tex);

    SDL_Texture* lose_screen_tex = window.loadTexture("res/gfx/lose_screen.png");
    background lose_screen(150, 170, 545, 457, lose_screen_tex);

    //tạo ra bloon
    SDL_Texture* red_bloon_tex = window.loadTexture("res/gfx/red_bloon.png");
    SDL_Texture* blue_bloon_tex = window.loadTexture("res/gfx/blue_bloon.png");
    SDL_Texture* green_bloon_tex = window.loadTexture("res/gfx/green_bloon.png");
    SDL_Texture* yellow_bloon_tex = window.loadTexture("res/gfx/yellow_bloon.png");

    std::map<int, SDL_Texture*> bloon_type;
    bloon_type[1] = red_bloon_tex;
    bloon_type[2] = blue_bloon_tex;
    bloon_type[3] = green_bloon_tex;
    bloon_type[4] = yellow_bloon_tex;

    std::vector<bloon> bloon_v;
    int bloon_count = 15;
    
    //tạo ra dart monkey
    SDL_Texture* dart_monkey_tex = window.loadTexture("res/gfx/dart_monkey-removebg-preview.png");
    std::vector<monkey> dart_monkey_v;

    //tạo ra dart
    SDL_Texture* dart_texture = window.loadTexture("res/gfx/dart_projectile.png");
    std::vector<projectile> dart_v;
    bool dart_monkey_go_with_mouse = false;

    //timer
    timer spawn_timer(100);
    timer round_timer(10);
    timer has_hit_timer(40);

    //tạo ra player
    player slimebuck(20, 0, 1);

    //tạo music 
    Music* main_theme;
    main_theme = new Music("music/Btd 6 Main Theme.mp3");
    main_theme->playMusic(-1);

    bool gameRunning = true;
    bool gameStarted = false;
    bool win = false;
    bool gameEnded = false;

    int mouse_x, mouse_y;

    SDL_Event event;

    while(gameRunning) {        

        //handle event của game
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
				gameRunning = false;
            if(event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&mouse_x, &mouse_y);
            }

            //start game
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_SPACE && !gameStarted) {
                    gameStarted = true;
                    slimebuck.modify_money(75);
                }
                else if(event.key.keysym.sym == SDLK_r && gameEnded) {
                    gameEnded = false;

                    slimebuck.money = 75;
                    slimebuck.health = 20;
                    slimebuck.round = 1;

                    for(int i=0; i<(int)bloon_v.size(); i++) {
                        bloon_v.erase(bloon_v.begin() + i);
                    }
                    for(int i=0; i<(int)dart_monkey_v.size(); i++) {
                        dart_monkey_v.erase(dart_monkey_v.begin() + i);
                    }
                    for(int i=0; i<(int)dart_v.size(); i++) {
                        dart_v.erase(dart_v.begin() + i);
                    }

                    bloon_count = 15;
                    spawn_timer.get_time_to_max();
                    round_timer.get_time_to_max();
                    has_hit_timer.get_time_to_max();
                }
            }

            //đặt monkey
            if(event.button.button == SDL_BUTTON_LEFT) {
                if(mouse_x >= 1039 && mouse_x <= 1129 && mouse_y >= 315 && mouse_y <= 402) {
                    if(slimebuck.money < 50) continue;
                    else {
                        dart_monkey_go_with_mouse = true;
                        monkey dart_monkey(vectorR2(mouse_x-30, mouse_y-30), dart_monkey_tex);
                        dart_monkey_v.push_back(dart_monkey);
                        slimebuck.modify_money(-50);
                    }
                }
                if(dart_monkey_go_with_mouse && mouse_x < 1000) {
                    dart_monkey_go_with_mouse = false;
                }
            }

            //bán monkey
            if(event.button.button == SDL_BUTTON_RIGHT) {
                for(int i=0; i<(int)dart_monkey_v.size(); i++) {
                    if(dart_monkey_v[i].getPos().x <= mouse_x && dart_monkey_v[i].getPos().x + 60 >= mouse_x &&
                       dart_monkey_v[i].getPos().y <= mouse_y && dart_monkey_v[i].getPos().y + 60 >= mouse_y) {
                        dart_monkey_v.erase(dart_monkey_v.begin() + i);
                        slimebuck.modify_money(25);
                    }
                }
            }
        }

        //cho dart monkey di chuyển theo chuột va chưa bắn khi chưa đặt
        if (!dart_monkey_v.empty()) {
            int last_monkey = dart_monkey_v.size() - 1;
            if (dart_monkey_go_with_mouse) {
                dart_monkey_v[last_monkey].move(mouse_x - 30, mouse_y - 30);
                dart_monkey_v[last_monkey].can_shoot = false;
            } else {
                dart_monkey_v[last_monkey].can_shoot = true;
            }
        }

        window.clear();

        window.render_background(bg);
        
        window.render_status(slimebuck);

        
        if(gameStarted && !gameEnded) {
            //spawn bloons theo round
            spawn_timer.time_passed();
            switch(slimebuck.round) {
                case 1:
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 1);
                    break;
                case 2:
                    create_bloon(bloon_count, 5, bloon_v, spawn_timer, 1);
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 2);
                    break;
                case 3:
                    create_bloon(bloon_count, 7, bloon_v, spawn_timer, 1);
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 3);
                    break;
                case 4:
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 2);
                    break;
                case 5:
                    create_bloon(bloon_count, 6, bloon_v, spawn_timer, 2);
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 3);
                    break;
                case 6:
                    create_bloon(bloon_count, 4, bloon_v, spawn_timer, 2);
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 4);
                    break;
                case 7:
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 3);
                    break;
                case 8:
                    create_bloon(bloon_count, 10, bloon_v, spawn_timer, 2);
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 4);
                    break;
                case 9:
                    create_bloon(bloon_count, 6, bloon_v, spawn_timer, 3);
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 4);
                    break;
                case 10:
                    create_bloon(bloon_count, 0, bloon_v, spawn_timer, 4);
                    break;
            }

            //qua round mới
            if(bloon_v.empty() && bloon_count == 0) {
                round_timer.time_passed();
                if(round_timer.time_is_zero() && slimebuck.round <= 10) {
                    slimebuck.modify_round();
                    round_timer.get_time_to_max();  
                    bloon_count = 15;         
                } 
            }
        }

        //bloons do stuff
        for(int i=0; i<(int)bloon_v.size(); i++) {
            if(!bloon_v[i].alive()) {
                bloon_v.erase(bloon_v.begin() + i);
            }
            else {
                bloon_v[i].tex = bloon_type[bloon_v[i].getHealth()];

                window.render_bloon(bloon_v[i]);

                bloon_v[i].bloon_move();

                if(bloon_v[i].bloon_reach_end()) {
                    slimebuck.modify_health(-bloon_v[i].getHealth());
                    slimebuck.modify_money(bloon_v[i].getHealth());
                }
            }
        }

        //render dart monkey 
        for(auto &dart_monkey : dart_monkey_v) {
            window.render_monkey(dart_monkey);
            dart_monkey.time_since_last_shot ++;
        }

        //render dart projectile
        for(int i=0; i<(int)dart_v.size(); i++) {
            window.render_dart(dart_v[i]);
        }

        //dart monkey tấn công mục tiêu
        for(auto &dart_monkey : dart_monkey_v) {
            if(!dart_monkey.target && !bloon_v.empty()) {
                dart_monkey.update_target(bloon_v);
            }

            // tạo ra dart khi dart monkey bắn
            if(dart_monkey.target != nullptr && dart_monkey.can_shoot && dart_monkey.shoot(slimebuck)) {
                projectile darts(vectorR2(dart_monkey.getPos().x+30, dart_monkey.getPos().y+30), dart_texture, dart_monkey.target->getPos());
                dart_v.push_back(darts);
            }
        }

        //dart di chuyển
        for(int i=0; i<(int)dart_v.size(); i++) {
            dart_v[i].move();
            if(dart_v[i].destroy() || dart_v[i].getPos().x > window_w || dart_v[i].getPos().y > window_h) { 
                dart_v.erase(dart_v.begin() + i);
            }
        }

        //kiểm tra va chạm giữa dart và bloon
        for(int i = 0; i < (int)dart_v.size(); i++) {
            for(int j = 0; j < (int)bloon_v.size(); j++) {
                SDL_Rect dart_rect = { (int)dart_v[i].getPos().x, (int)dart_v[i].getPos().y, 20, 16 };
                SDL_Rect bloon_rect = { (int)bloon_v[j].getPos().x, (int)bloon_v[j].getPos().y, 32, 40 };

                if(SDL_HasIntersection(&dart_rect, &bloon_rect) && !dart_v[i].has_hit(bloon_v[j])) {
                    bloon_v[j].bloon_pop(slimebuck);
                    dart_v[i].pop();
                    dart_v[i].mark_hit(bloon_v[j]);

                    break;
                }
            }
        }
        
        //timer cho dart khi bắn trúng 1 bloon thì không gây damage lên 1 bloon đấy, dùng để fix bug 1 dart gây damage 2 lần 
        for(int i=0; i<(int)bloon_v.size(); i++) {
            if(bloon_v[i].has_hit) {
                has_hit_timer.time_passed();
                if(has_hit_timer.time_is_zero()) {
                    bloon_v[i].has_hit = false;
                    has_hit_timer.get_time_to_max();
                }
            }
            else continue;
        }

        if(!gameStarted) {
            window.render_background(start_bg);
        }

        if(slimebuck.round == 10 && bloon_v.empty()) {
            gameEnded = true;
            win = true;
        }

        if(slimebuck.health <= 0) {
            gameEnded = true;
            win = false;
            for(int i=0; i<(int)bloon_v.size(); i++) {
                bloon_v.erase(bloon_v.begin() + i);
            }
        }

        if (gameEnded) {
            if(win) {
                window.render_background(end_screen);
            }
            else {
                window.render_background(lose_screen);
            }
        }



        window.display();

        SDL_Delay(8);

    } 

    window.cleanUp();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    main_theme->~Music();
    
    return 0;
}