#pragma once
#include "gameObject/gameObject.h"
#include "animation/animation.h"
#include <string>
#include <unordered_map>


class Animator : public Component{

    public:
        Animator(GameObject& associated);
        void Update(float dt);
        void Render();
        void SetAnimation(std::string name);
        void AddAnimation(std::string name, Animation anim);
    private:
        std::unordered_map<std::string,Animation> animations;
        int frameStart;
        int frameEnd;
        int frameTime;
        int currentFrame;
        float timeElapsed;
};