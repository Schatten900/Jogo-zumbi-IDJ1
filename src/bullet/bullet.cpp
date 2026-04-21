#include "bullet/bullet.h"
#include "animator/animator.h"
#include "spriteRenderer/spriteRenderer.h"
#include "game/game.h"
#include <cmath>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance) : Component(associated){

    //=============
    // Association
    //=============

    SpriteRenderer* sr = new SpriteRenderer(associated,"assets/img/Bullet.png",1,1);
    associated.AddComponent(sr);

    sr->SetScale(0.5, 0.5); 

    associated.angleDeg = angle * 180 / M_PI;


    //=============
    // Atributtes
    //=============

    this->speed = Vec2(cos(angle),sin(angle)) * speed;

    this->distanceLeft = maxDistance;
    this->damage = damage;

}

void Bullet::Update(float dt){

    Vec2 displacement = speed * dt;
    associated.box = associated.box + displacement;

    distanceLeft -= displacement.magnitude();

    if (distanceLeft <= 0 ) associated.RequestDelete();    

}

void Bullet::Render(){}

int Bullet::GetDamage(){
    return this->damage;
}