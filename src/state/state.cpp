#include "state/state.h"
#include "zombie/zombie.h"
#include "spriteRenderer/spriteRenderer.h"

State::State(){
    quitRequested = false;
    LoadAssets();
    music.Play(-1);
}

State::~State(){
    objectArray.clear();
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){
    // Background
    GameObject* bgGO = new GameObject();
    bgGO->box = Rect(0, 0, 0, 0);

    bgGO->AddComponent(
        new SpriteRenderer(*bgGO, "assets/img/Background.png")
    );

    AddObject(bgGO);

    // Zombie
    GameObject* zombieGO = new GameObject();
    zombieGO->box = Rect(600, 450, 0, 0);

    zombieGO->AddComponent(new Zombie(*zombieGO));

    AddObject(zombieGO);

    // Music
    music.Open("assets/audio/BGM.wav");
}

void State::Update(float dt){
    //if (SDL_QuitRequested()) quitRequested = true;
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }

    for(size_t i = 0; i < objectArray.size(); ){
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        } else {
            i++;
        }
    }

}
void State::Render(){
    //bg.Render(0, 0);
        for(int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void State::AddObject(GameObject* go){
    objectArray.emplace_back(go);
}
