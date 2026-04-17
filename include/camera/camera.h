#pragma once
#include "gameObject/gameObject.h"
#include "vec2/vec2.h"


class Camera {
    public:
        static void Follow(GameObject* newFocus);
        static void Unfollow();
        static void Update(float dt);

        static Vec2 pos;
        static Vec2 speed;
    private:
        static GameObject* focus;
};