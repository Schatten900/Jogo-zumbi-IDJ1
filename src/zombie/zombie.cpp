#include "zombie/zombie.h"
#include "spriteRenderer/spriteRenderer.h"
#include "animator/animator.h"
#include "inputManager/inputManager.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), hitPoints(100), deathSound("assets/audio/Dead.wav"), hitSound("assets/audio/Hit0.wav")
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

    int mouseX = InputManager::GetInstance().GetMouseX();
    int mouseY = InputManager::GetInstance().GetMouseY();
    Vec2 mouseVec(mouseX, mouseY);
    
    if (!associated.box.contains(mouseVec)) return;

    hitPoints -= damage;
    hitSound.Play(1);

    if(hitPoints <= 0){
        Animator* anim = associated.GetComponent<Animator>();
        if(anim) anim->SetAnimation("dead");

        deathSound.Play(1);
    }
}

void Zombie::Update(float dt){
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) Damage(10);
}

void Zombie::Render(){

}