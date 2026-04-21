#include "gun/gun.h"
#include "animator/animator.h"
#include "spriteRenderer/spriteRenderer.h"
#include "bullet/bullet.h"
#include "game/game.h"
#include "inputManager/inputManager.h"
#include "camera/camera.h"
#include <cmath>

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character) : 
Component(associated),
cooldownState(0), 
shotSound("assets/audio/Range.wav"), 
reloadSound("assets/audio/PumpAction.mp3"){

    //===================
    // Association
    //===================
    this->character = character;

    SpriteRenderer* sr = new SpriteRenderer(associated,"assets/img/Gun.png",3,2);
    associated.AddComponent(sr);

    //===================
    // Animation
    //===================
    Animator* anim = new Animator(associated);
    anim->AddAnimation("idle",Animation(0,2,0));
    anim->AddAnimation("reloading",Animation(3,5,0.1f));
    anim->SetAnimation("idle");
    associated.AddComponent(anim);
}

void Gun::Update(float dt){

    // Atualiza o timer de cooldown
    cdTimer.Update(dt);

    auto charPtr = character.lock();
    if (!charPtr){
        associated.RequestDelete();
        return;
    }

    //===========
    //  Angle
    //===========
    InputManager& im = InputManager::GetInstance();

    int mouseX = im.GetMouseX();
    int mouseY = im.GetMouseY();

    Vec2 target(mouseX, mouseY);

    Vec2 direction = target - charPtr->box.getCenter();
    direction = direction.normalize();

    angle = direction.angle();

    // rad -> graus 
    associated.angleDeg = angle * 180 / M_PI;

    //===========
    //  Gun pos
    //===========
    Vec2 center = charPtr->box.getCenter();

    float dist = 32; // distância da arma ao player
    Vec2 offset = Vec2(cos(angle), sin(angle)) * dist;

    associated.box.setX(center.getX() + offset.getX() - associated.box.getW()/2);
    associated.box.setY(center.getY() + offset.getY() - associated.box.getH()/2);

    //===========
    //  States
    //===========
    if (cooldownState == 1 && cdTimer.Get() > 0.1f){
        // Estado 1 → indo para recarregar
        cooldownState = 2;
        cdTimer.Restart();

        Animator* anim = associated.GetComponent<Animator>();
        if (anim) anim->SetAnimation("reloading");

        reloadSound.Play(1);
    }

    else if (cooldownState == 2 && cdTimer.Get() > 0.2f ){
        // Estado 2 → terminou recarga
        cooldownState = 3;
        cdTimer.Restart();

        Animator* anim = associated.GetComponent<Animator>();
        if (anim) anim->SetAnimation("idle");
    }

    else if (cooldownState == 3 && cdTimer.Get() > 0.1f){
        // Estado 3 → pronto para atirar novamente
        cooldownState = 0;
    }

    //===========
    //  Flip
    //===========
    SpriteRenderer* sr = associated.GetComponent<SpriteRenderer>();

    if (sr){
        if (angle > M_PI/2 || angle < -M_PI/2) 
            sr->SetFlip(SDL_FLIP_VERTICAL);
        else 
            sr->SetFlip(SDL_FLIP_NONE);
    }
}

void Gun::Render(){}

void Gun::Shoot(Vec2 target){

    // Só atira se estiver pronto
    if (cooldownState != 0) return;

    auto charPtr = character.lock();
    if (!charPtr) return;

    //===========
    //  Bullet
    //===========
    GameObject* bulletGO = new GameObject();

    float dist = 32;
    Vec2 offset = Vec2(cos(angle), sin(angle)) * dist;

    bulletGO->box = Rect(
        associated.box.getCenter().getX() + offset.getX(),
        associated.box.getCenter().getY() + offset.getY(),
        64, 64 
    );

    float speed = 1000;       
    float damage = 20;
    float maxDistance = 2000;

    bulletGO->AddComponent(new Bullet(*bulletGO, angle, speed, damage, maxDistance));
    Game::GetInstance().GetState().AddObject(bulletGO);

    //===========
    //  Sound
    //===========
    shotSound.Play(1);

    cooldownState = 1;
    cdTimer.Restart();
}