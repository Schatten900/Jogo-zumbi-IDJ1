
#include "collider/collider.h"
#include "gameObject/gameObject.h"

//============
//  Constructor
//============
Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated){
    this->scale = scale;
    this->offset = offset;
}

//=============
//  Methods
//=============
void Collider::Update(float dt){
    box = associated.box;

    // Scales
    box.setW(associated.box.getW() * scale.getX());
    box.setH(associated.box.getH() * scale.getY());

    Vec2 center = associated.box.getCenter();

    // Offset
    Vec2 rotatedOffset = offset.rotate(associated.angleDeg);

    box.setX(center.getX() + rotatedOffset.getX() - box.getW()/2);
    box.setY(center.getY() + rotatedOffset.getY() - box.getH()/2);

}

void Collider::Render(){}

//============
//  Setters
//============
void Collider::SetScale(Vec2 scale){
    this->scale = scale;
}
void Collider::SetOffSet(Vec2 offset){
    this->offset = offset;
}