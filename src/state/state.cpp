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

State::State(){
    quitRequested = false;
    started = false;
}

State::~State(){
    objectArray.clear();
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){

    // TileSet
    TileSet* ts = new TileSet(64,64,"assets/img/Tileset.png");

    // TileMap
    GameObject* tmGO = new GameObject();
    tmGO->box = Rect(0,0,0,0);
    tmGO->AddComponent(
        new TileMap(*tmGO,"assets/map/map.txt",ts)
    );

    AddObject(tmGO);

    // Background
    GameObject* bgGO = new GameObject();
    bgGO->box = Rect(0, 0, 0, 0);

    SpriteRenderer* bg = new SpriteRenderer(*bgGO, "assets/img/Background.png");
    bg->SetCameraFollower(true);

    bgGO->AddComponent(bg);
    AddObject(bgGO);

    // Music
    music.Open("assets/audio/BGM.wav");

    // Player
    GameObject* charGO = new GameObject();
    charGO->box = Rect(600,600,64,64);
    charGO->AddComponent(new Character(*charGO,"assets/img/Player.png"));
    charGO->AddComponent(new PlayerController(*charGO));
    AddObject(charGO);

    Camera::Follow(charGO);
}

void State::Update(float dt){

    //===============================
    //  Inputs
    //===============================
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) quitRequested = true;   
    if (InputManager::GetInstance().KeyPress(SPACE_KEY)){
        int mouseX = InputManager::GetInstance().GetMouseX();
        int mousey = InputManager::GetInstance().GetMouseY();
        GameObject* zombieGO = new GameObject();
        zombieGO->box = Rect(mouseX,mousey,64,64);
        zombieGO->AddComponent(new Zombie(*zombieGO));
        AddObject(zombieGO);
    }

    //===============================
    //  Renderização dos objetos
    //===============================
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }

    //===============================
    //  Remoção dos objetos
    //===============================
    for(size_t i = 0; i < objectArray.size(); ){
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        } else {
            i++;
        }
    }
    Camera::Update(dt);

}
void State::Render(){

    for (auto go : objectArray) go->Render();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
    std::shared_ptr<GameObject> ptr(go);
    objectArray.push_back(ptr);
    if (started) ptr->Start();

    return std::weak_ptr<GameObject>(ptr);
}

std::weak_ptr< GameObject > State::GetObjectPtr(GameObject* go){
    for (auto& go_aux : objectArray){
        if (go_aux.get() == go ) return std::weak_ptr<GameObject>(go_aux);
    }
    return std::weak_ptr<GameObject>();
}

void State::Start(){
    LoadAssets();
    music.Play(-1);
    for (auto& go : objectArray){
        go->Start();
    }
    started = true;
}
 

