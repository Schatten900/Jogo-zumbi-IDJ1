#pragma once
#include "vec2/vec2.h"

class Player{
    public:
        Vec2 pos;
        Vec2 vel;
        float speed;

        Player(float x, float y);
        void update(float dt);
};