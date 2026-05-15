#pragma once
#include "component/component.h"
#include "rect/rect.h"
#include <vector>
#include <algorithm>
#include <memory>

class Component;

class GameObject{
    public:

        //==============
        // Constructor
        //==============
        GameObject();
        ~GameObject();

        //==============
        // Methods
        //==============
        void Update(float dt);
        void Render();

        bool IsStarted()  const;
        bool IsDead() const ;
        void RequestDelete();

        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);

        void Start();

        void NotifyCollision(GameObject& other);


        //==============
        // Attributes
        //==============
        double angleDeg;
        Rect box;

        //==============
        // Getters
        //==============
        template <class T>
        T* GetComponent() {
            for(size_t i = 0; i < components.size(); i++){
                T* component = dynamic_cast<T*>(components[i].get());
                if(component != nullptr) return component;
            }
            return nullptr;
        }

    private:
        //==============
        // Attributes
        //==============
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;

        bool started;


};