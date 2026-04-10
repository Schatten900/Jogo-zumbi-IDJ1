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
        associated.box.getH()
    );
}
void SpriteRenderer::SetFrame(int frame){
    sprite.SetFrame(frame);
}