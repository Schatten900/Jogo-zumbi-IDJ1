#include "sprite/sprite.h"
#include "game/game.h"

Sprite::Sprite(){
    texture = nullptr;
    width = 0;
    height = 0;
}
Sprite::Sprite(std::string file){
    texture = nullptr;
    width = 0;
    height = 0;
    Open(file);
}
Sprite::~Sprite(){
    if (texture != nullptr) SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file){
    if (texture != nullptr) SDL_DestroyTexture(texture);

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {std::cout << SDL_GetError() << '\n'; return;}
    SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
    SetClip(0, 0, width, height);

}
void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}
void Sprite::Render(int x, int y){
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect
    );
}

int Sprite::GetHeight(){
    return height;
}
int Sprite::GetWidth(){
    return width;
}
bool Sprite::isOpen(){
    return texture != nullptr;
}
