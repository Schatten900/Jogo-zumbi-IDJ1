#pragma once
#include "state/state.h"

class TitleState : public State {
    public:
        //============
        //  Queue
        //============

        TitleState();
        ~TitleState();

        //============
        //  Methods
        //============
        void LoadAssets();
        void Update(float dt);
        void Render();

        //============
        //  Queue
        //============
        void Start();
        void Pause();
        void Resume();
    
    private:

};