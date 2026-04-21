#pragma once
#include "component/component.h"
#include "vec2/vec2.h"
#include "timer/timer.h"
#include <memory>
#include <string>
#include <queue>

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

        // Jogador
        static Character* player;

    private:
        std::weak_ptr<GameObject> gun;

        std::queue<Command> taskQueue;

        Vec2 speed;
        float linearSpeed;
        int hp;

        Timer deathTimer;

};