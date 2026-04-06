#pragma once

#include "state/state.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>

class Game{
    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
    private:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        Game(std::string, int width, int height);
};
