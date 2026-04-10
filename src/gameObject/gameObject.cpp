#include "gameObject/gameObject.h"

GameObject::GameObject(){
    this->isDead = false;
}

GameObject::~GameObject(){
    for(int i = components.size() - 1; i >= 0; i--){
        delete components[i];
    }
    components.clear();
}

void GameObject::Update(float dt){
    for(Component*cpt : components){
        cpt->Update(dt);
    }
}

void GameObject::Render(){
    for(Component*cpt : components){
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
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt){
    auto it = std::find(components.begin(), components.end(), cpt);
    if(it != components.end()){
        delete *it;
        components.erase(it);
    }
}

