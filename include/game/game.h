#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "state/state.h"

class Game{
    public:

        //===============
        //  Constructor
        //===============
        Game(std::string, int width, int height);
        ~Game();

        //===============
        //  Methods
        //===============
        void Run();
        void Push(State* state);
        void CalculateDeltaTime();

        //===============
        //  Getters
        //===============
        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();
        float GetDeltaTime();


    private:

        //===============
        //  Attributes
        //===============

        static Game* instance;

        State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::stack<std::unique_ptr<State>> stateStack;

        float dt = 0;
        int frameStart;
};
