    #include "aicontroller/aiController.h"
    #include "character/character.h"
    #include "spriteRenderer/spriteRenderer.h"
    #include "animator/animator.h"
    #include "collider/collider.h"
    #include "bullet/bullet.h"
    #include "game/game.h"

    int AiController::npcCounter = 0;

    AiController::AiController(GameObject& associated) 
        : 
        Component(associated),
        speed(150),
        deathSound("assets/audio/Dead.wav"), 
        hitSound("assets/audio/Hit0.wav"),
        tookDamage(false),
        hit(false),
        hp(80)
        {
        state = AiController::RESTING;
        SpriteRenderer* sr =
            new SpriteRenderer(associated, "assets/img/NPC.png", 3, 4);

        associated.AddComponent(sr);

        // Animator
        Animator* anim = new Animator(associated);
        anim->AddAnimation("walking", Animation(0, 5, 0.06f));
        anim->AddAnimation("idle", Animation(6, 8, 0.2f));
        anim->AddAnimation("dead", Animation(9, 11, 0));
        anim->SetAnimation("walking");
        associated.AddComponent(anim);

        //===================
        // Collision
        //===================

        associated.AddComponent(new Collider(associated));
        npcCounter++;
    };

    AiController::~AiController(){
        npcCounter--;
    }

    void AiController::Update(float dt){

        auto playerGO = Character::player.lock();
        if (!playerGO) return;


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
        if (hit && hp > 0 && hitTimer.Get() > 0.5f){
            if(anim) anim->SetAnimation("walking");
            hit = false;
        }

        if (hp <= 0) {
            if (deathTimer.Get() > 0.5f){
                associated.RequestDelete();
            }
            return;
        }

        //============ 
        //  RESTING
        //============
        if (state == RESTING){
            restTimer.Update(dt);
            if(anim) anim->SetAnimation("idle");
            if (restTimer.Get() > 2.0f){ 
                destination = playerGO->box.getCenter();
                state = MOVING;
            }
        }

        //============ 
        //  Walking
        //============
        if (state == MOVING){

            Vec2 pos = associated.box.getCenter();
            Vec2 direction = (destination - pos).normalize();
            Vec2 velocity = direction * speed;

            associated.box = associated.box + velocity * dt;

            float distance = pos.distance(destination);

            if(anim) anim->SetAnimation("walking");

            SpriteRenderer* sr = associated.GetComponent<SpriteRenderer>();
            
            if (sr) {
                if (velocity.getX() < 0) 
                    sr->SetFlip(SDL_FLIP_HORIZONTAL);
                else 
                    sr->SetFlip(SDL_FLIP_NONE);
            }

            Vec2 playerPos = playerGO->box.getCenter();

            auto gunPtr = gun.lock();
            if (gunPtr){
                Gun* gunComp = gunPtr->GetComponent<Gun>();
                if (gunComp){
                    gunComp->SetTarget(playerPos);
                } 
            }

            //============ 
            //  Shooting
            //============
            if (distance < 20.0f){
                if (gunPtr){
                    Gun* gunComp = gunPtr->GetComponent<Gun>();
                    if (gunComp){
                        gunComp->SetTarget(playerPos);
                        gunComp->Shoot(playerPos);
                    } 
                }
                restTimer.Restart();
                state = RESTING;
            }

            tookDamage = false;
        }
    }

    void AiController::Render(){}

    void AiController::Start(){
        auto self = Game::GetInstance().GetState().GetObjectPtr(&associated);

        Vec2 center = associated.box.getCenter();

        auto gunGO = std::make_shared<GameObject>();
        gunGO->box = Rect(center.getX(), center.getY(), 64, 64);

        gunGO->AddComponent(new Gun(*gunGO, self));

        gun = Game::GetInstance().GetState().AddObject(gunGO);
    }

    int AiController::GetHP(){
        return this->hp;
    }

    void AiController::Damage(int damage){

        if (associated.IsDead()) return;
        if(hp <= 0) return;
        if(tookDamage) return;

        tookDamage = true;
        hp -= damage;
        hitSound.Play(1);

        Animator* anim = associated.GetComponent<Animator>();
        if(hp > 0){
            hit = true;
            hitTimer.Restart();
        }
        else{
            if(anim) anim->SetAnimation("dead");
            deathSound.Play(1);
            deathTimer.Restart();
        }
    }

    void AiController::NotifyCollision(GameObject& other) {

        if (associated.IsDead()) return;
        if (other.IsDead()) return;
        if (hp <= 0) return;

        Collider* col = other.GetComponent<Collider>();
        if (!col) return;

        Bullet* bullet = other.GetComponent<Bullet>();

        if (bullet){
            Damage(bullet->GetDamage());
            if (associated.IsDead()) return;    
        }

    }