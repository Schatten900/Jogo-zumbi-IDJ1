#include "zombie/zombie.h"
#include "spriteRenderer/spriteRenderer.h"
#include "animator/animator.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), hitPoints(100), deathSound("assets/audio/Dead.wav")
{
    // Sprite
    SpriteRenderer* sr =
        new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);
    associated.AddComponent(sr);

    // Animator
    Animator* anim = new Animator(associated);
    anim->AddAnimation("walking", Animation(0, 3, 10));
    anim->AddAnimation("dead", Animation(5, 5, 0));
    anim->SetAnimation("walking");
    associated.AddComponent(anim);

}

void Zombie::Damage(int damage){
    if(hitPoints <= 0) return;

    hitPoints -= damage;

    if(hitPoints <= 0){
        Animator* anim = associated.GetComponent<Animator>();
        if(anim) anim->SetAnimation("dead");

        deathSound.Play(1);
    }
}

void Zombie::Update(float dt){
    Damage(1);
}

void Zombie::Render(){

}