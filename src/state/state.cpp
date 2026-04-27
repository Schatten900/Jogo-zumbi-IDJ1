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
    auto tmGO = std::make_shared<GameObject>();
    tmGO->box = Rect(0,0,0,0);
    tmGO->AddComponent(
        new TileMap(*tmGO,"assets/map/map.txt",ts)
    );

    AddObject(tmGO);

    // Background
    auto bgGO = std::make_shared<GameObject>();
    bgGO->box = Rect(0, 0, 0, 0);

    SpriteRenderer* bg = new SpriteRenderer(*bgGO, "assets/img/Background.png");
    bg->SetCameraFollower(true);

    bgGO->AddComponent(bg);
    AddObject(bgGO);

    // Music
    music.Open("assets/audio/BGM.wav");

    // Player
    auto charGO = std::make_shared<GameObject>();
    charGO->box = Rect(600,600,64,64);
    charGO->AddComponent(new Character(*charGO,"assets/img/Player.png"));
    charGO->AddComponent(new PlayerController(*charGO));
    AddObject(charGO);

    Camera::Follow(charGO);

}

void State::Update(float dt){


    Camera::Update(dt);
    //===============================
    //  Inputs
    //===============================
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) quitRequested = true;   
    if (InputManager::GetInstance().KeyPress(SPACE_KEY) && !startedWave){
        //Zombies
        auto waveGO = std::make_shared<GameObject>();
        waveGO->AddComponent(new WaveSpawner(*waveGO));
        AddObject(waveGO);
        waveGO->Start();
        startedWave = true;
    }

    //======================
    //  UPDATE
    //======================
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }

    //======================
    // Collider
    //======================

    for(int i=0; i< objectArray.size(); i++){
        for (int j= i+1; j < objectArray.size(); j++){
            auto aPtr = objectArray[i];
            auto bPtr = objectArray[j];

            GameObject* a = aPtr.get();
            GameObject* b = bPtr.get();

            if (a->IsDead() || b->IsDead()) continue;
            if (!a || !b) continue; 

            Collider* a_collider = a->GetComponent<Collider>();
            Collider* b_collider = b->GetComponent<Collider>();

            if(a_collider && b_collider){
                if(a_collider->box.intersects(b_collider->box)){
                    if (a->IsDead() || b->IsDead()) continue;

                    a->NotifyCollision(*b);

                    if (a->IsDead() || b->IsDead()) continue;

                    b->NotifyCollision(*a);
                }
            }
        }
    }

    //====================
    //  REMOVE
    //====================
    for(size_t i = 0; i < objectArray.size(); ){
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        } else {
            i++;
        }
    }


}
void State::Render(){
    for (auto go : objectArray) go->Render();
}

std::weak_ptr<GameObject> State::AddObject(std::shared_ptr<GameObject> go){
    objectArray.push_back(go);
    if (started) go->Start();

    return std::weak_ptr<GameObject>(go);
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
    startedWave = false;
    started = true;
}
 

