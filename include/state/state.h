#pragma once
#include "music/music.h"
#include "sprite/sprite.h"
#include "gameObject/gameObject.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

class State{

    public:

        //===============
        //  Constructor
        //===============
        State();
        virtual ~State();

        //===============
        //  Requested
        //===============
        bool virtual QuitRequested();
        bool virtual PopRequested();

        //===============
        //  Methods
        //===============
        void virtual LoadAssets() = 0;
        void virtual Update(float dt) = 0;
        void virtual Render() = 0;

        //===============
        //  Array
        //===============
        void virtual StartArray();
        void virtual UpdateArray(float dt);
        void virtual RenderArray();
        
        //===============
        //  Queue
        //===============
        void virtual Start() = 0; 
        void virtual Pause() = 0;
        void virtual Resume() = 0;

    
        std::weak_ptr< GameObject >  virtual AddObject(std::shared_ptr<GameObject> go);
        std::weak_ptr< GameObject > virtual GetObjectPtr(GameObject* go); 

        //===============
        //  Setters
        //===============
        void SetPopRequested(bool requested);
        void SetQuitRequested(bool requested);

    protected:
        //===============
        //  attributes
        //===============
        bool quitRequested;
        bool started;
        bool popRequested;
        
        //================
        //  Object Array
        //================
        std::vector< std::shared_ptr< GameObject > > objectArray;

};