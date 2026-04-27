#include "zombie/zombie.h"
#include "spriteRenderer/spriteRenderer.h"
#include "animator/animator.h"
#include "inputManager/inputManager.h"
#include "camera/camera.h"
#include "collider/collider.h"
#include "bullet/bullet.h"
#include "character/character.h"

int Zombie::zombieCount = 0;

Zombie::Zombie(GameObject& associated)
    : 
    Component(associated), hitPoints(100), 
    deathSound("assets/audio/Dead.wav"), 
    hitSound("assets/audio/Hit0.wav"), 
    hit(false), hitDamage(10),
    speed(100),
    tookDamage(false)
{
    // Sprite
    SpriteRenderer* sr =
        new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);
    associated.AddComponent(sr);

    // Animator
    Animator* anim = new Animator(associated);
    anim->AddAnimation("walking", Animation(0, 3, 0.06f));
    anim->AddAnimation("dead", Animation(5, 5, 0));
    anim->AddAnimation("hit", Animation(4, 4, 0.15f));
    anim->SetAnimation("walking");
    associated.AddComponent(anim);

    //===================
    // Collision
    //===================

    associated.AddComponent(new Collider(associated));
    zombieCount ++;

}

Zombie::~Zombie(){
    zombieCount--;
}

void Zombie::Damage(int damage){

    if (associated.IsDead()) return;
    if(hitPoints <= 0) return;
    if(tookDamage) return;

    tookDamage = true;
    hitPoints -= damage;
    hitSound.Play(1);

    Animator* anim = associated.GetComponent<Animator>();
    if(hitPoints > 0){
        hit = true;
        hitTimer.Restart();
        if(anim) anim->SetAnimation("hit");
    }

    else{
        if(anim) anim->SetAnimation("dead");
        deathSound.Play(1);
        deathTimer.Restart();
    }
}

void Zombie::Update(float dt){

    if (associated.IsDead()) return;
    //==========
    // Updating
    //===========

    hitTimer.Update(dt);
    deathTimer.Update(dt);

    //==========
    // hit
    //===========
    Animator* anim = associated.GetComponent<Animator>();
    if (hit && hitPoints > 0 && hitTimer.Get() > 0.5f){
        if(anim) anim->SetAnimation("walking");
        hit = false;
    }

    if (hitPoints <= 0) {
        if (deathTimer.Get() > 0.5f){
            associated.RequestDelete();
        }
        return;
    }

    //==========
    // walking
    //===========

    auto playerGO = Character::player.lock();
    if (!playerGO) return;

    Vec2 currentPos = associated.box.getCenter();
    Vec2 target = playerGO->box.getCenter();

    Vec2 direction = target - currentPos;
    direction = direction.normalize();

    Vec2 velocity = direction * speed;
    Vec2 displacement = velocity * dt;

    associated.box = associated.box + displacement;


    SpriteRenderer* sr = associated.GetComponent<SpriteRenderer>();

    if (sr) {
        if (velocity.getX() < 0) 
            sr->SetFlip(SDL_FLIP_HORIZONTAL);
        else 
            sr->SetFlip(SDL_FLIP_NONE);
    }

    tookDamage = false;
}

void Zombie::Render(){}

void Zombie::NotifyCollision(GameObject& other) {

    if (associated.IsDead()) return;
    if (other.IsDead()) return;
    if (hitPoints <= 0) return;

    Collider* col = other.GetComponent<Collider>();
    if (!col) return;

    Bullet* bullet = other.GetComponent<Bullet>();

    if (bullet){
        Damage(bullet->GetDamage());
        if (associated.IsDead()) return;    
    }
}

int Zombie::GetDamage(){
    return this->hitDamage;
}

int Zombie::GetHP(){
    return this->hitPoints;
}
