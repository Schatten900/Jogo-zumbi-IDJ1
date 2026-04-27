#include "sound/sound.h"
#include "resources/resources.h"
#include <iostream>


//==============
// Constructor
//==============

Sound::Sound() : chunk(nullptr), channel(-1) {}

Sound::Sound(std::string file)
    : Sound()
{
    Open(file);
}


//==============
// Methods
//==============

void Sound::Play(int times){
    if(chunk == nullptr) return;
    channel = Mix_PlayChannel(-1, chunk, times-1);
}

void Sound::Stop(){
    Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
    chunk = Resources::GetSound(file);
}

bool Sound::isOpen(){
    return this->chunk != nullptr;
}