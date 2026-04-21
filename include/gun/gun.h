#pragma once
#include "component/component.h"
#include "vec2/vec2.h"
#include <memory>
#include "sound/sound.h"
#include "timer/timer.h"


class Gun : public Component {

    public:
        Gun(GameObject& associated, std::weak_ptr<GameObject> character);
        void Update(float dt);
        void Render();
        void Shoot(Vec2 target);

    private:
        Sound shotSound;
        Sound reloadSound;
        
        int cooldownState;
        Timer cdTimer;

        std::weak_ptr< GameObject > character;
        float angle;
};