#include "state/state.h"
#include "zombie/zombie.h"
#include "spriteRenderer/spriteRenderer.h"
#include "tileset/tileset.h"
#include "tilemap/tilemap.h"
#include "inputManager/inputManager.h"
#include "camera/camera.h"
#include "character/character.h"
#include "playerController/playerController.h"
#include <algorithm>
#include "collider/collider.h"
#include "waveSpawner/waveSpawner.h"

//===============
//  Constructor
//===============
State::State(){
    quitRequested = false;
    started = false;
    popRequested = false;
}

State::~State(){
    objectArray.clear();
}

//===============
//  Queue
//===============
bool State::QuitRequested(){
    return quitRequested;
}

bool State::PopRequested(){
    return popRequested;
}

//===============
//  GameObject
//===============

std::weak_ptr<GameObject> State::AddObject(std::shared_ptr<GameObject> go){
    objectArray.push_back(go);

    return std::weak_ptr<GameObject>(go);
}

std::weak_ptr< GameObject > State::GetObjectPtr(GameObject* go){
    for (auto& go_aux : objectArray){
        if (go_aux.get() == go ) return std::weak_ptr<GameObject>(go_aux);
    }
    return std::weak_ptr<GameObject>();
}

//===============
//  Array
//===============
void State::StartArray(){
    for (size_t i = 0; i < objectArray.size(); i++){
        auto elem = objectArray[i];
        elem->Start();
    }
}

void State::UpdateArray(float dt){
    for (size_t i = 0; i < objectArray.size(); i++){

        auto elem = objectArray[i];

        if (!elem->IsStarted())
            elem->Start();

        elem->Update(dt);
    }
}

void State::RenderArray(){
    for (size_t i = 0; i < objectArray.size(); i++){
        auto elem = objectArray[i];
        elem->Render();
    }
}
 
void State::SetPopRequested(bool requested){
    this->popRequested = requested;
}
void State::SetQuitRequested(bool requested){
    this->quitRequested = requested;
}   