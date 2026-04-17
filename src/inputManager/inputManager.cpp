#include "inputManager/inputManager.h"

// ===================================
//      Singleton
// ===================================

InputManager&  InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}

InputManager::InputManager(){
    for (int i=0; i< 6; i++){
        mouseState[i] = false;
    }
    updateCounter = 0;
    quitRequested =false;
    mouseX = 0;
    mouseY = 0;
    
}

InputManager::~InputManager(){}

// ===================================
//      Atualização
// ===================================

void InputManager::Update(){

    updateCounter++;
    quitRequested = false;

    SDL_Event event;

    SDL_GetMouseState(&mouseX,&mouseY);

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT: {
                quitRequested = true;
                break;
            }
            case SDL_KEYDOWN:{
                if (event.key.repeat == 0) {
                    int key = event.key.keysym.sym;
                    keyState[key] = true;
                    keyUpdate[key] = updateCounter;
                }
                break;
            }
            case SDL_KEYUP:{
                int key = event.key.keysym.sym;
                keyState[key] = false;
                keyUpdate[key] = updateCounter;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                int button = event.button.button;
                mouseState[button] = true;
                mouseUpdate[button] = updateCounter;
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                int button = event.button.button;
                mouseState[button] = false;
                mouseUpdate[button] = updateCounter;
                break;
            }
        }

    }

}

// ===================================
//      Teclas
// ===================================

bool InputManager::KeyPress(int key){
    return keyState[key] == true && keyUpdate[key] == updateCounter;
}
bool InputManager::KeyRelease(int key){
    return keyState[key] == false && keyUpdate[key] == updateCounter;
}
bool InputManager::IsKeyDown(int key){
    return keyState[key];
}

// ===================================
//      Mouse
// ===================================

bool InputManager::MousePress(int button){
    return mouseState[button] == true && mouseUpdate[button] == updateCounter;
}
bool InputManager::MouseRelease(int button){
    return mouseState[button] == false && mouseUpdate[button] == updateCounter;
}
bool InputManager::IsMouseDown(int button){
    return mouseState[button];
}

// ===================================
//      Getters
// ===================================

int InputManager::GetMouseX(){
    return mouseX;
}
int InputManager::GetMouseY(){
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequested;
}
