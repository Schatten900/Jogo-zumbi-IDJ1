#pragma once
#include "component/component.h"
#include "vec2/vec2.h"
#include "rect/rect.h"

class Collider : public Component{

    public:
        //============
        //  Constructor
        //============
        Collider(GameObject& associated, Vec2 scale = {1,1}, Vec2 offset = {0,0});

        //=============
        //  Methods
        //=============
        void Update(float dt);
        void Render();
        //============
        //  Setters
        //============
        void SetScale(Vec2 scale);
        void SetOffSet(Vec2 offset);
        
        Rect box;

    private:
        //============
        //  Attributes
        //============
        Vec2 scale;
        Vec2 offset;


};