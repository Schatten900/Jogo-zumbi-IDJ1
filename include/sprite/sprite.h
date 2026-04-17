#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite{
    public:
        Sprite();
        Sprite(std::string file);

        Sprite(std::string file,int frameCountW = 1, int frameCountH = 1);

        ~Sprite();

        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);

        void SetFrame(int frame);
        void SetFrameCount(int frameCountW, int frameCountH);

        void Render(int x, int y);
        void Render(int x, int y, int w, int h);

        int GetHeight();
        int GetWidth();
        bool isOpen();

        bool cameraFollower;

    private:
        SDL_Texture* texture;
        int width;
        int height;
        int frameCountW;
        int frameCountH;
        SDL_Rect clipRect;

};