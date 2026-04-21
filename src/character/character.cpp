#include "character/character.h"
#include "animator/animator.h"
#include "spriteRenderer/spriteRenderer.h"
#include "gun/gun.h"
#include "game/game.h"

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string sprite) : Component(associated), linearSpeed(200){

    if (player == nullptr) {
        player = this;
    }

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

}

Character::~Character(){
    if (player == this) player = nullptr;
}

void Character::Start(){
    auto charSelf = Game::GetInstance().GetState().GetObjectPtr(&associated);

    Vec2 center = associated.box.getCenter();

    GameObject* gunGO = new GameObject();
    gunGO->box = Rect(
        center.getX() + 32, 
        center.getY(),
        64, 64
    ); 
    gunGO->AddComponent(new Gun(*gunGO,charSelf));
    gun = Game::GetInstance().GetState().AddObject(gunGO);

}

void Character::Update(float dt){

    speed = Vec2(0,0);
    bool moved = false;

    while (!taskQueue.empty()){
        auto task = taskQueue.front();
        taskQueue.pop();

        if (task.type == Command::MOVE){

            Vec2 direction = task.pos.normalize();
            direction = direction.normalize();
            speed = direction * linearSpeed;
            associated.box = associated.box + (speed * dt);
            moved = true;
        }
        else{
            auto gunPtr = gun.lock();
            if (gunPtr){
                Gun* gunComp = gunPtr->GetComponent<Gun>();
                if (gunComp) gunComp->Shoot(task.pos);
            }
        }
    }

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
}

void Character::Issue(Command task){
    taskQueue.push(task);
}

void Character::Render(){}