#include "gameObject/gameObject.h"

GameObject::GameObject(){
    this->isDead = false;
    this->started = false;
    this->angleDeg = 0.0f;
}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Update(float dt){

    if (isDead) return;

    for(auto& cpt : components){
        cpt->Update(dt);
        if (isDead) return;
    }
}

void GameObject::Render(){
    for(auto& cpt : components){
        cpt->Render();
    }
}

bool GameObject::IsDead() const{
    return this->isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    components.emplace_back(cpt);
    if(started) cpt->Start();
}


void GameObject::RemoveComponent(Component* cpt){
    auto it = std::find_if(components.begin(), components.end(),
        [cpt](const std::unique_ptr<Component>& comp){
            return comp.get() == cpt;
        });

    if(it != components.end()){
        components.erase(it); 
    }
}

void GameObject::Start(){

    for (auto& cp : components){
        cp->Start();
    }
    started = true;
}


void GameObject::NotifyCollision(GameObject& other){
    if (isDead) return;

    for (auto& elem : components){
        elem->NotifyCollision(other);
        if (isDead) return;
    }
}