#include "camera/camera.h"
#include "inputManager/inputManager.h"
#include "game/game.h"

Vec2 Camera::pos(0,0);
Vec2 Camera::speed(0,0);
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}
void Camera::Unfollow(){
    focus = nullptr;
}
void Camera::Update(float dt){

    if (focus){
        int h,w;
        SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &w, &h);
        pos.setX(focus->box.getX() + focus->box.getW()/2 - w/2);
        pos.setY(focus->box.getY() + focus->box.getH()/2 - h/2);
        return;
    }
    InputManager& im = InputManager::GetInstance();

    speed.setX(0);
    speed.setY(0);

    if (im.IsKeyDown(LEFT_ARROW_KEY)) speed.setX(-500);
    if (im.IsKeyDown(RIGHT_ARROW_KEY)) speed.setX(500);
    if (im.IsKeyDown(UP_ARROW_KEY)) speed.setY(-500);
    if (im.IsKeyDown(DOWN_ARROW_KEY)) speed.setY(500);
    pos += speed * dt;

}