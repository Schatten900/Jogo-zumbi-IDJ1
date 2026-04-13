#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound{
    public:
        Sound();
        Sound(std::string file);
        ~Sound();


        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool isOpen();
    private:
        Mix_Chunk* chunk;
        int channel;
};