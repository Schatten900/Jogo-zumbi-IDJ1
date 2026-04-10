#include "animation/animation.h"
       
Animation::Animation(int frameStart, int frameEnd, float frameTime){
    this->frameStart = frameStart;
    this->frameEnd = frameEnd;
    this-> frameTime = frameTime;
}
int Animation::getFrameStart(){
    return this->frameStart;
}

int Animation::getFrameEnd(){
    return this->frameEnd;
}

float Animation::getFrameTime(){
    return this->frameTime;
}

void Animation::setFrameStart(int frameStart){
    this->frameStart = frameStart;
}

void Animation::setFrameEnd(int frameEnd){
    this->frameEnd = frameEnd;
}

void Animation::setFrameTime(float frameTime){
    this->frameTime = frameTime;
}