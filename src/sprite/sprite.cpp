#include "sprite/sprite.h"
#include "game/game.h"
#include "resources/resources.h"
#include "camera/camera.h"


// =====================================================
// Construction
// =====================================================

Sprite::Sprite(){
    texture = nullptr;
    width = 0;
    height = 0;
    frameCountW = 1;
    frameCountH = 1;
    scale = Vec2(1,1);
    flip = SDL_FLIP_NONE;
    cameraFollower = false;
}
Sprite::Sprite(std::string file){
    texture = nullptr;
    width = 0;
    height = 0;
    scale = Vec2(1,1);
    flip = SDL_FLIP_NONE;
    cameraFollower = false;
    Open(file);
}

Sprite::Sprite(std::string file,int frameCountW, int frameCountH){
    texture = nullptr;
    width = 0;
    height = 0;
    scale = Vec2(1,1);
    flip = SDL_FLIP_NONE;
    this->frameCountH = frameCountH;
    this->frameCountW = frameCountW;
    cameraFollower = false;
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file){
    texture = Resources::GetImage(file);
    if(texture == nullptr) return;

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetFrame(0);

}

// =====================================================
// Render
// =====================================================

void Sprite::Render(int x, int y, float angle){

    SDL_Rect dstRect;

    if(cameraFollower){
        dstRect.x = x;
        dstRect.y = y;
    }
    else{
        dstRect.x = x - Camera::pos.getX();
        dstRect.y = y - Camera::pos.getY();
    }

    dstRect.w = clipRect.w * scale.getX();
    dstRect.h = clipRect.h * scale.getY();


    SDL_RenderCopyEx(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect,
        angle,
        nullptr,
        flip
    );
}

void Sprite::Render(int x, int y, int w, int h, float angle){
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w * scale.getX();
    dstRect.h = h * scale.getY();

    SDL_RenderCopyEx(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect,
        angle,
        nullptr,
        flip
    );
}


// =====================================================
// Getters and Setters
// =====================================================

int Sprite::GetHeight(){
    return (height / frameCountH) * scale.getY();
}
int Sprite::GetWidth(){
    return (width / frameCountW) * scale.getX();
}

Vec2 Sprite::GetScale(){
    return scale;
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::SetFrame(int frame){
    int frameW = width / frameCountW;
    int frameH = height / frameCountH;

    int row = frame / frameCountW;
    int col = frame % frameCountW;

    int clipX = col * frameW;
    int clipY = row * frameH;

    SetClip(clipX, clipY, frameW, frameH);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH){
    this->frameCountH = frameCountH;
    this->frameCountW = frameCountW;
}

void Sprite::SetScale(float scaleX, float scaleY){
    if (scaleX != 0) scale.setX(scaleX);
    if (scaleY != 0) scale.setY(scaleY);
}

void Sprite::SetFlip(SDL_RendererFlip flip){
    this->flip = flip;
}

bool Sprite::isOpen(){
    return texture != nullptr;
}
