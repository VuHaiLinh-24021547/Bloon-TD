#ifndef MUSIC_HPP_INCLUDE
#define MUSIC_HPP_INCLUDE

#pragma once

#include <SDL2/SDL_mixer.h>
#include <iostream>

class Music{
    public:
        Music(const char* filepath) {
            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
                std::cout << "Audio library not working: " << Mix_GetError() << std::endl; 
            }

            music = Mix_LoadMUS(filepath);
            if(!music)  {
                std::cout<< "Mix_LoadMUS(filepath) is not working: " << Mix_GetError() << std::endl;
            }

            sound_effect = Mix_LoadWAV(filepath);
        }

        //-1 is forever loop
        void playMusic(int loops) {
            if(music != nullptr) {
                if(Mix_PlayMusic(music, loops) == -1) {
                    std::cout<< "Mix_PlayMusic(music, loops) is not working: " << Mix_GetError() << std::endl;
                }
            }
        }

        void playPopSound() {
            Mix_PlayChannel(-1, sound_effect, 0);
        }

        void pauseMusic() {
            Mix_PauseMusic();
        }

        void setVolume(int volume) {
            Mix_VolumeMusic(volume);
        }

        ~Music() {
            Mix_FreeMusic(music);
            music = NULL;
        }
    private:
        Mix_Music *music;

        Mix_Chunk* sound_effect;
};

#endif