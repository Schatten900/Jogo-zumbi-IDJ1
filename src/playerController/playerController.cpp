#include "playerController/playerController.h"
#include "inputManager/inputManager.h"
#include "character/character.h"
#include "camera/camera.h"

PlayerController::PlayerController(GameObject& associated) :Component(associated){}

void PlayerController::Update(float dt){
    InputManager& im = InputManager::GetInstance();
    Character* character = associated.GetComponent<Character>();
    if (!character) return;

    Vec2 direction(0,0);

    //===============
    // Movimentation
    //===============
    if (im.IsKeyDown(W_KEY)) direction.setY(-1);
    if (im.IsKeyDown(S_KEY)) direction.setY(1);
    if (im.IsKeyDown(A_KEY)) direction.setX(-1);
    if (im.IsKeyDown(D_KEY)) direction.setX(1);

    if (direction.magnitude() > 0 ){
        character->Issue(Character::Command(Character::Command::MOVE,direction.getX(),direction.getY()));
    }

    //===============
    // Shoot
    //===============
    if (im.MousePress(LEFT_MOUSE_BUTTON)){
        int mouseX = im.GetMouseX() + Camera::pos.getX();
        int mouseY = im.GetMouseY() + Camera::pos.getY();

        character->Issue(Character::Command(Character::Command::SHOOT,mouseX,mouseY));
    }
}


void PlayerController::Render(){}


void PlayerController::Start(){

}