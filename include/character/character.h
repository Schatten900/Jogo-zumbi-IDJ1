#pragma once
#include "component/component.h"
#include "vec2/vec2.h"
#include "timer/timer.h"
#include <memory>
#include <string>
#include <queue>
#include "sound/sound.h"
#include "timer/timer.h"

class Character : public Component {

    public:

        // =========================
        // Command (classe interna)
        // =========================
        class Command {
        public:
            enum CommandType {
                MOVE,
                SHOOT
            };

            CommandType type;
            Vec2 pos;

            Command(CommandType type, float x, float y)
                : type(type), pos(x, y) {}
        };


        // =========================
        // Construtores
        // =========================
        Character(GameObject& associated, std::string sprite);
        ~Character();


        // =========================
        // Metodos
        // =========================
        void Start();
        void Update(float dt);
        void Render();
        void Issue(Command task);

        void NotifyCollision(GameObject& other);

        void Damage(int);

        // Jogador
        static std::weak_ptr<GameObject> player;

    private:
        std::weak_ptr<GameObject> gun;

        std::queue<Command> taskQueue;

        //============
        // Attributes
        //============

        Vec2 speed;
        float linearSpeed;
        int hp;

        //==========
        // Sound
        //==========

        Sound hitSound;
        Sound deathSound;

        //==========
        // Timer
        //==========
        Timer deathTimer;
        Timer hitTimer;
        Timer damageTimer;

};