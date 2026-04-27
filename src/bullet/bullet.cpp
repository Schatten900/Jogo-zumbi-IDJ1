#include "bullet/bullet.h"
#include "animator/animator.h"
#include "spriteRenderer/spriteRenderer.h"
#include "game/game.h"
#include <cmath>
#include "collider/collider.h"
#include "zombie/zombie.h"
#include "character/character.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer) : Component(associated){

    //=============
    // Association
    //=============

    SpriteRenderer* sr = new SpriteRenderer(associated,"assets/img/Bullet.png",1,1);
    associated.AddComponent(sr);

    sr->SetScale(1.01, 1.01); 

    associated.angleDeg = angle * 180 / M_PI;

    //=============
    // Atributtes
    //=============

    this->speed = Vec2(cos(angle),sin(angle)) * speed;

    this->distanceLeft = maxDistance;
    this->damage = damage;  

    this->targetsPlayer = targetsPlayer;


    //===================
    // Collision
    //===================

    associated.AddComponent(new Collider(associated));

}

void Bullet::Update(float dt){

    if (associated.IsDead()) return;

    Vec2 displacement = speed * dt;
    associated.box = associated.box + displacement;

    distanceLeft -= displacement.magnitude();

    if (distanceLeft <= 0 ) {
        associated.RequestDelete();    
        return;
    }
}

void Bullet::Render(){}

int Bullet::GetDamage(){
    return this->damage;
}

bool Bullet::GetTargetsPlayer(){
    return this->targetsPlayer;
}

void Bullet::NotifyCollision(GameObject& other) {

    if (associated.IsDead()) return;
    if (other.IsDead()) return;

    Collider* col = other.GetComponent<Collider>();
    if (!col) return;


    //=============
    //  Player
    //=============

    Character* character = other.GetComponent<Character>();

    if (character){
        if (targetsPlayer){
            character->Damage(GetDamage());
            associated.RequestDelete();
        }
        return;
    }

    //=============
    //  Zombie
    //=============

    Zombie* zombie = other.GetComponent<Zombie>();

    if (zombie){
        if (zombie->GetHP() <= 0) return; 
        
        associated.RequestDelete();
        return;
    }


}