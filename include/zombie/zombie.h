#pragma once
#include "component/component.h"
#include "gameObject/gameObject.h"
#include "sound/sound.h"
#include "timer/timer.h"

class Zombie : public Component{
    public:
        //===========
        // Constructor
        //===========
        Zombie(GameObject & associated);
        ~Zombie();

        //===========
        // Methods
        //===========
        void Damage(int damage);
        void Update(float dt);
        void Render();
        void NotifyCollision(GameObject& other);

        //==========
        // Getters
        //==========

        int GetDamage();
        int GetHP();

        static int zombieCount;

    private:
        //===========
        // Attributes
        //===========
        int hitPoints;
        int hitDamage;
        float speed;
        bool tookDamage;

        //===========
        // Sound
        //===========
        Sound deathSound;
        Sound hitSound;

        //===========
        // Timers
        //===========
        Timer hitTimer;
        Timer deathTimer;
        bool hit;
};