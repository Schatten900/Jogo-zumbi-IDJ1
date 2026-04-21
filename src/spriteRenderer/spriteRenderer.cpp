#include "spriteRenderer/spriteRenderer.h"
#include "gameObject/gameObject.h"
#include "rect/rect.h"        

SpriteRenderer::SpriteRenderer(GameObject& associated)
    : Component(associated), sprite() {}

SpriteRenderer::SpriteRenderer(GameObject& associated, 
    std::string file, 
    int frameCountW, 
    int frameCountH) : Component(associated), sprite(file,frameCountW,frameCountH)
{
    associated.box = Rect(associated.box.getX(), associated.box.getY(),sprite.GetWidth(), sprite.GetHeight());
    sprite.SetFrame(0);
}

void SpriteRenderer::Open(std::string file){
    sprite.Open(file);

    associated.box = Rect(
        associated.box.getX(),
        associated.box.getY(),
        sprite.GetWidth(),
        sprite.GetHeight()
    );
}
void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH){
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::Update(float dt){

}

void SpriteRenderer::Render(){
    sprite.Render(
        associated.box.getX(),
        associated.box.getY(),
        associated.box.getW(),
        associated.box.getH(),
        associated.angleDeg
    );
}
void SpriteRenderer::SetFrame(int frame){
    sprite.SetFrame(frame);
}

void SpriteRenderer::SetCameraFollower(bool val){
    sprite.cameraFollower = val;
}

Sprite& SpriteRenderer::GetSprite(){
    return sprite;
}

void SpriteRenderer::SetScale(float scaleX, float scaleY){
    Vec2 center = associated.box.getCenter();
    sprite.SetScale(scaleX,scaleY);

    associated.box.setH(sprite.GetHeight());
    associated.box.setW(sprite.GetWidth());

    associated.box.setX(center.getX() - (associated.box.getW()/2));
    associated.box.setY(center.getY() - (associated.box.getH()/2));
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip){
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}

void SpriteRenderer::SetFlip(SDL_RendererFlip flip){
    sprite.SetFlip(flip);
}