#pragma once
#include "music/music.h"
#include "sprite/sprite.h"
#include "gameObject/gameObject.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "state/state.h"

class StageState : public State {

    public:
        //==============
        //  Constructor
        //==============
        StageState();
        ~StageState();

        //==============
        //  Methods
        //==============
        void LoadAssets();
        void Update(float dt);
        void Render();

        //==============
        //  Queue
        //==============
        void Start(); 
        void Pause();
        void Resume();

    private:
        Music music;
        bool startedWave;
};