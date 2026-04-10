#pragma once
#include "component/component.h"
#include "rect/rect.h"
#include <vector>
#include <algorithm>

class Component;

class GameObject{
    public:

        Rect box;

        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();

        bool IsDead() const ;
        void RequestDelete();

        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);

        template <class T>
        T* GetComponent() {
        for(size_t i = 0; i < components.size(); i++){
            T* component = dynamic_cast<T*>(components[i]);
            if(component != nullptr){
                return component;
            }
        }
    return nullptr;
}

    private:
        std::vector<Component*> components;
        bool isDead;
};