#pragma once
#include <SDL2/SDL.h>

class Animation{
    public:

        //==============
        // Constructor
        //==============
        Animation();
        Animation(int frameStart, int FrameEnd, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE);

        //==============
        // Getters
        //==============
        int getFrameStart();
        int getFrameEnd();
        float getFrameTime();
        
        //==============
        // Setters
        //==============
        void setFrameStart(int frameStart);
        void setFrameEnd(int frameEnd);
        void setFrameTime(float frameTime);

         //==============
        // Atributtes
        //==============
        SDL_RendererFlip flip;

    private:
        //==============
        // Atributtes
        //==============
        int frameStart;
        int frameEnd;
        float frameTime;
};