#include "endState/endState.h"
#include "inputManager/inputManager.h"
#include "titleState/titleState.h"
#include "game/game.h"
#include "gameData/gameData.h"
#include "spriteRenderer/spriteRenderer.h"

EndState::EndState(){
    if (GameData::playerVictory){
        auto victoryGO = std::make_shared<GameObject>();
        victoryGO->box = Rect(0, 0, 0, 0);

        SpriteRenderer* bgVictory = new SpriteRenderer(*victoryGO, "assets/img/Win.png");

        victoryGO->AddComponent(bgVictory);
        AddObject(victoryGO);
        backgroundMusic.Open("assets/audio/endStateWin.ogg");
    }
    else{
        auto defeatGO = std::make_shared<GameObject>();
        defeatGO->box = Rect(0, 0, 0, 0);

        SpriteRenderer* bgDefeat = new SpriteRenderer(*defeatGO, "assets/img/Lose.png");
        
        defeatGO->AddComponent(bgDefeat);
        AddObject(defeatGO);
        backgroundMusic.Open("assets/audio/endStateLose.ogg");
    }
}


EndState::~EndState(){}

void EndState::Update(float dt){
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
       quitRequested = true;
    }   
    if (InputManager::GetInstance().KeyPress(SPACE_KEY)){
        Game::GetInstance().Push(new TitleState());
        popRequested = true;
    }
}

void EndState::Render(){
    RenderArray();
}

void EndState::Start(){
    LoadAssets();
    backgroundMusic.Play(-1);
    started = true;
    StartArray();
}

void EndState::Pause(){}

void EndState::Resume(){}

void EndState::LoadAssets(){}