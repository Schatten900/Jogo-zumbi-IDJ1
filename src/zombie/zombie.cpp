#include "zombie/zombie.h"
#include "spriteRenderer/spriteRenderer.h"
#include "animator/animator.h"
#include "inputManager/inputManager.h"
#include "camera/camera.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), hitPoints(100), deathSound("assets/audio/Dead.wav"), hitSound("assets/audio/Hit0.wav"), hit(false)
{
    // Sprite
    SpriteRenderer* sr =
        new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);
    associated.AddComponent(sr);

    // Animator
    Animator* anim = new Animator(associated);
    anim->AddAnimation("walking", Animation(0, 3, 10));
    anim->AddAnimation("dead", Animation(5, 5, 0));
    anim->AddAnimation("hit", Animation(4, 4, 0.1f));
    anim->SetAnimation("walking");
    associated.AddComponent(anim);

}

void Zombie::Damage(int damage){
    if(hitPoints <= 0) return;

    int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.getX();
    int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.getY();
    Vec2 mouseVec(mouseX, mouseY);
    
    if (!associated.box.contains(mouseVec)) return;

    hitPoints -= damage;
    hitSound.Play(1);

    Animator* anim = associated.GetComponent<Animator>();
    if(hitPoints > 0){
        hit = true;
        hitTimer.Restart();
        if(anim) anim->SetAnimation("hit");
    }

    if(hitPoints <= 0){
        Animator* anim = associated.GetComponent<Animator>();
        if(anim) anim->SetAnimation("dead");

        deathSound.Play(1);
        deathTimer.Restart();
    }
}

void Zombie::Update(float dt){
    hitTimer.Update(dt);
    deathTimer.Update(dt);
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) Damage(10);

    Animator* anim = associated.GetComponent<Animator>();
    if (hit && hitPoints > 0 && hitTimer.Get() > 0.5f){
        if(anim) anim->SetAnimation("walking");
        hit = false;
    }

    if (hitPoints <= 0 && deathTimer.Get() >0.5f) associated.RequestDelete();

}

void Zombie::Render(){

}