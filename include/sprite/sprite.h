#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vec2/vec2.h"

class Sprite{
    public:

        //==============
        // Constructor
        //==============
        Sprite();
        Sprite(std::string file);

        Sprite(std::string file,int frameCountW = 1, int frameCountH = 1);

        ~Sprite();


        void Open(std::string file);
        //==============
        // Setters
        //==============

        void SetClip(int x, int y, int w, int h);

        void SetFrame(int frame);
        void SetFrameCount(int frameCountW, int frameCountH);

        void SetScale(float scaleX,float scaleY);

        void SetFlip(SDL_RendererFlip flip);

        //==============
        // Render
        //==============
        void Render(int x, int y,float angle = 0);
        void Render(int x, int y, int w, int h,float angle = 0);

        //==============
        // Getters
        //==============
        int GetHeight();
        int GetWidth();
        Vec2 GetScale();

        //==============
        // Utils
        //==============
        bool isOpen();
        bool cameraFollower;

    private:
        //==============
        // Details
        //==============
        SDL_Texture* texture;
        int width;
        int height;

        //==============
        // Frames
        //==============
        int frameCountW;
        int frameCountH;
        SDL_Rect clipRect;

        //==============
        // Rotation
        //==============
        SDL_RendererFlip flip;
        Vec2 scale;

};