#include "animation/animation.h"
       

//==============
// Constructor
//==============

Animation::Animation() : frameStart(0), frameEnd(0), frameTime(0), flip(SDL_FLIP_NONE) {}

Animation::Animation(int start, int end, float time, SDL_RendererFlip flip)
    : frameStart(start), frameEnd(end), frameTime(time), flip(flip){}


//==============
// Getters
//==============
int Animation::getFrameStart(){
    return this->frameStart;
}

int Animation::getFrameEnd(){
    return this->frameEnd;
}

float Animation::getFrameTime(){
    return this->frameTime;
}


//==============
// Setters
//==============
void Animation::setFrameStart(int frameStart){
    this->frameStart = frameStart;
}

void Animation::setFrameEnd(int frameEnd){
    this->frameEnd = frameEnd;
}

void Animation::setFrameTime(float frameTime){
    this->frameTime = frameTime;
}