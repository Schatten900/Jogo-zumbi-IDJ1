#pragma once
#include "component/component.h"
#include <SDL2/SDL.h>

class PlayerController : public Component{

    public:
    PlayerController (GameObject& associated);
    void Start();
    void Update (float dt);
    void Render ();

};