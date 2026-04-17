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
    cameraFollower = false;
}
Sprite::Sprite(std::string file){
    texture = nullptr;
    width = 0;
    height = 0;
    cameraFollower = false;
    Open(file);
}

Sprite::Sprite(std::string file,int frameCountW, int frameCountH){
    texture = nullptr;
    width = 0;
    height = 0;
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

void Sprite::Render(int x, int y){

    SDL_Rect dstRect;

    if(cameraFollower){
        dstRect.x = x;
        dstRect.y = y;
    }
    else{
        dstRect.x = x - Camera::pos.getX();
        dstRect.y = y - Camera::pos.getY();
    }

    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;


    SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect
    );
}

void Sprite::Render(int x, int y, int w, int h){
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;

    SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect
    );
}



// =====================================================
// Getters and Setters
// =====================================================

int Sprite::GetHeight(){
    return height / frameCountH;
}
int Sprite::GetWidth(){
    return width / frameCountW;
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

bool Sprite::isOpen(){
    return texture != nullptr;
}
