#include "state/state.h"

State::State(){
    quitRequested = false;
    LoadAssets();
    music.Play(-1);
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){
    bg.Open("assets/img/Background.png");
    music.Open("assets/audio/BGM.wav");
}

void State::Update(float dt){
    if (SDL_QuitRequested()) quitRequested = true;
}
void State::Render(){
    bg.Render(0, 0);
}
