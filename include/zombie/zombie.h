#pragma once
#include "component/component.h"
#include "gameObject/gameObject.h"
#include "sound/sound.h"

class Zombie : public Component{
    public:
        Zombie(GameObject & associated);
        void Damage(int damage);
        void Update(float dt);
        void Render();
    private:
        int hitPoints;
        Sound deathSound;
};