#pragma once
#include "gameObject/gameObject.h"
#include "vec2/vec2.h"
#include <memory>

class Camera {
    public:
        static void Follow(std::shared_ptr<GameObject> newFocus);
        static void Unfollow();
        static void Update(float dt);

        static Vec2 pos;
        static Vec2 speed;
    private:
        static std::weak_ptr<GameObject> focus;
};