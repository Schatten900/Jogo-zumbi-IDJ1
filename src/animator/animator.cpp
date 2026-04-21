#include "animator/animator.h"
#include "spriteRenderer/spriteRenderer.h"

Animator::Animator(GameObject& associated)
    : Component(associated),
      frameStart(0),
      frameEnd(0),
      frameTime(0),
      currentFrame(0),
      timeElapsed(0)
{
}

void Animator::Update(float dt){
    if (frameTime == 0) return;
    timeElapsed +=dt;

    while (timeElapsed >= frameTime) {
        currentFrame ++;
        timeElapsed -= frameTime;
    }

    if (currentFrame > frameEnd) currentFrame = frameStart;
    
     SpriteRenderer* sr =
            associated.GetComponent<SpriteRenderer>();

    if(sr != nullptr) sr->SetFrame(currentFrame);
        
}

void Animator::Render(){

}

void Animator::SetAnimation(std::string name){
    auto it = animations.find(name);
    if (it == animations.end()) return;
    if (it->first != current) {
        
        current = it->first;
        frameEnd = it->second.getFrameEnd();
        frameStart = it->second.getFrameStart();
        frameTime = it->second.getFrameTime();
        currentFrame = frameStart;
        timeElapsed = 0;

        SpriteRenderer* sr = associated.GetComponent<SpriteRenderer>();
        if (sr != nullptr) sr->SetFrame(currentFrame, animations[current].flip);
    }
    
}

void Animator::AddAnimation(std::string name, Animation anim){
    if(animations.find(name) == animations.end()){
        animations.insert({name, anim});
    }
}

