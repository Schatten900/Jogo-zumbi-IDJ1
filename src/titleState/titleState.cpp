#include "titleState/titleState.h"
#include "stageState/stageState.h"
#include "inputManager/inputManager.h"
#include <algorithm>
#include "game/game.h"
#include "spriteRenderer/spriteRenderer.h"


//==============
//  Constructor
//==============
TitleState::TitleState(){}

TitleState::~TitleState(){}

//============
//  Methods
//============
void TitleState::LoadAssets(){
    auto titleGO = std::make_shared<GameObject>();
    titleGO->AddComponent(
        new SpriteRenderer(*titleGO, "assets/img/Title.png")
    );
    AddObject(titleGO);
}

void TitleState::Update(float dt){
   if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) quitRequested = true;  
   if (InputManager::GetInstance().KeyPress(SPACE_KEY)){
        Game::GetInstance().Push(new StageState());
        popRequested = true;
   }

}
void TitleState::Render(){
    RenderArray();
}

//============
//  Queue
//============
void TitleState::Start(){
    LoadAssets();
    started = true;
    StartArray();
}

void TitleState::Pause(){}

void TitleState::Resume(){}