#include "character/character.h"
#include "animator/animator.h"
#include "spriteRenderer/spriteRenderer.h"
#include "gun/gun.h"
#include "game/game.h"
#include "collider/collider.h"
#include "zombie/zombie.h"
#include "camera/camera.h"
#include "bullet/bullet.h"
#include "inputManager/inputManager.h"


std::weak_ptr<GameObject> Character::player;

Character::Character(GameObject& associated, std::string sprite) 
    :
    Component(associated), 
    linearSpeed(200), 
    hp(100),
    hitSound("assets/audio/Hit1.wav"), deathSound("assets/audio/Dead.wav"){

    damageTimer.Restart();

    //===================
    // Association
    //====================

    SpriteRenderer* charGO = new SpriteRenderer(associated,"assets/img/Player.png",3,4);
    associated.AddComponent(charGO);

    //===================
    // Animation
    //====================

    Animator* anim = new Animator(associated);
    anim->AddAnimation("idle",Animation(9,9,0));
    anim->AddAnimation("walking",Animation(0,8,0.06f));
    anim->AddAnimation("dead",Animation(10,11,0));
    anim->SetAnimation("idle");
    associated.AddComponent(anim);

    //===================
    // Collision
    //===================

    associated.AddComponent(new Collider(associated));

}

Character::~Character(){
   player.reset();
}

void Character::Start(){

    
    auto charSelf = Game::GetInstance().GetState().GetObjectPtr(&associated);

    player = charSelf;
    
    Vec2 center = associated.box.getCenter();

    auto gunGO = std::make_shared<GameObject>();
    gunGO->box = Rect(
        center.getX() + 32, 
        center.getY(),
        64, 64
    ); 
    gunGO->AddComponent(new Gun(*gunGO,charSelf));
    gun = Game::GetInstance().GetState().AddObject(gunGO);

}

void Character::Update(float dt){


    //============
    //  Updating
    //============
    damageTimer.Update(dt);
    hitTimer.Update(dt);
    deathTimer.Update(dt);

    speed = Vec2(0,0);
    bool moved = false;


    //============
    // AIM 
    //============
    auto gunPtr = gun.lock();
    if (gunPtr){
        Gun* gunComp = gunPtr->GetComponent<Gun>();
        if (gunComp){
            InputManager& im = InputManager::GetInstance();
            Vec2 mouse(im.GetMouseX(), im.GetMouseY());
            gunComp->SetTarget(mouse);
        }
    }

    //============
    //  Tasks
    //============
    while (!taskQueue.empty()){
        auto task = taskQueue.front();
        taskQueue.pop();

        if (task.type == Command::MOVE){

            Vec2 direction = task.pos.normalize();
            speed = direction * linearSpeed;
            associated.box = associated.box + (speed * dt);
            moved = true;
        }
        else{
            auto gunPtr = gun.lock();
            if (gunPtr){
                Gun* gunComp = gunPtr->GetComponent<Gun>();
                if (gunComp) {
                    gunComp->Shoot(task.pos);
                }
            }
        }
    }

    //============
    //  Sprite
    //============
    Animator* anim = associated.GetComponent<Animator>();
    if(anim){
        if (moved) 
            anim->SetAnimation("walking");
        else 
            anim->SetAnimation("idle");
    }

    SpriteRenderer* sr = associated.GetComponent<SpriteRenderer>();

    if (sr) {
        if (speed.getX() < 0) 
            sr->SetFlip(SDL_FLIP_HORIZONTAL);
        else 
            sr->SetFlip(SDL_FLIP_NONE);
    }

    //============
    //  Death
    //============
    if (hp <= 0 && deathTimer.Get() >0.5f){
        Camera::Unfollow();
        player.reset();
        associated.RequestDelete();
    } 
}

void Character::Issue(Command task){
    taskQueue.push(task);
}

void Character::Render(){}


void Character::Damage(int damage){

    if(hp <= 0) return;
    if (damageTimer.Get() < 0.5f) return;
    
    hp -= damage;
    hitSound.Play(1);
    
    if(hp > 0){
        hitTimer.Restart();
    }
    else{
        Animator* anim = associated.GetComponent<Animator>();
        if(!anim) return;
        anim->SetAnimation("dead");
        deathSound.Play(1);
        deathTimer.Restart();
    }
}


void Character::NotifyCollision(GameObject& other) {

    if (associated.IsDead()) return;
    if (other.IsDead()) return;

    Collider* col = other.GetComponent<Collider>();
    if (!col) return;

    //===========
    //  Zombie
    //===========

    Zombie* zombie = other.GetComponent<Zombie>();

    if (zombie && damageTimer.Get() > 1.0f){
        Damage(zombie->GetDamage());
        damageTimer.Restart();
        return;
    }
}