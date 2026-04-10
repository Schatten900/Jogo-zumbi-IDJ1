#pragma once
#include "music/music.h"
#include "sprite/sprite.h"
#include "gameObject/gameObject.h"
#include <SDL2/SDL.h>
#include <vector>

class State{

    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

        void AddObject(GameObject* go);

    private:
        Music music;
        bool quitRequested;

        std::vector<std::unique_ptr<GameObject>> objectArray;
};