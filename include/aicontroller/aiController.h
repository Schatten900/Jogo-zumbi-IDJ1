#pragma once
#include "gameObject/gameObject.h"
#include "timer/timer.h"
#include "vec2/vec2.h"
#include "gun/gun.h"
#include "sound/sound.h"

class AiController : public Component
{
    public:
        AiController(GameObject& associated);
        ~AiController();

        //=========
        // Methods
        //=========
        void Update(float dt);
        void Render();
        void Start();
        void NotifyCollision(GameObject& other);
        void Damage(int damage);

        //=========
        // Getters
        //=========

        int GetHP();

        static int npcCounter;

    private:

        //=========
        // State
        //=========
        enum AiState {MOVING, RESTING};

        AiState state;

        //=========
        // Timers
        //=========
        Timer restTimer;
        Timer hitTimer;
        Timer deathTimer;

        //=========
        // Attributes
        //=========
        float speed;
        int hp;
        bool tookDamage;
        bool hit;
        Vec2 destination;

        std::weak_ptr<GameObject> gun;

        //=========
        // Sound
        //=========
        Sound hitSound;

        Sound deathSound;

};