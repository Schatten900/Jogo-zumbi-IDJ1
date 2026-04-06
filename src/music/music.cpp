#include "music/music.h"

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file){
    music = nullptr;
    Open(file);
}

Music::~Music(){
    Stop();
    if (music != nullptr) Mix_FreeMusic(music);
}

void Music::Play(int times){
    if (music != nullptr) Mix_PlayMusic(music,times);
}

void Music::Stop(int msToStop ){
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file){
    if (music != nullptr) Mix_FreeMusic(music);
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) std::cout << Mix_GetError() << '\n';
}

bool Music::IsOpen(){
    return music != nullptr;
}