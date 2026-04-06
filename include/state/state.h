#pragma once
#include "music/music.h"
#include "sprite/sprite.h"
#include <SDL2/SDL.h>

class State{

    public:
        State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};