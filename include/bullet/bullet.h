#pragma once
#include "component/component.h"
#include "vec2/vec2.h"

class Bullet : public Component{

    public:
        //===========
        // Constructor
        //===========
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer);

        //===========
        // Methods
        //===========
        void Update(float dt);
        void Render();
        void NotifyCollision(GameObject& other);

        //===========
        // Getters
        //===========
        int GetDamage();
        bool GetTargetsPlayer();

    private:
        Vec2 speed;
        float distanceLeft;

        int damage;

        bool targetsPlayer;

};