#include "text/text.h"
#include "game/game.h"
#include "camera/camera.h"
#include "resources/resources.h"

Text::Text(
    GameObject& associated,
    std::string fontFile,
    int fontSize,
    TextStyle style,
    std::string text,
    SDL_Color color
) : Component(associated) {

    texture = nullptr;
    font = nullptr;

    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;

    RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    if (font != nullptr) {
        TTF_CloseFont(font);
    }
}

//==============
//  Methods
//==============
void Text::Update(float dt) {}

void Text::Render() {
    if (texture == nullptr) return;

    SDL_Rect clipRect;
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = associated.box.getW();
    clipRect.h = associated.box.getH();

    SDL_Rect dstRect;
    dstRect.x = associated.box.getX() - Camera::pos.getX();
    dstRect.y = associated.box.getY() - Camera::pos.getY();
    dstRect.w = associated.box.getW();
    dstRect.h = associated.box.getH();

    SDL_RenderCopyEx(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect,
        0,
        nullptr,
        SDL_FLIP_NONE
    );
}

//=================
//  Setters
//=================
void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if (font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    // Carrega fonte
    font = Resources::GetFont(fontFile.c_str(), fontSize);

    if (font == nullptr) {
        SDL_Log("Erro ao carregar fonte: %s", TTF_GetError());
        return;
    }

    SDL_Surface* surface = nullptr;

    // Cor preta 
    SDL_Color bg = {0, 0, 0, 255};

    // Cria a surface 
    if (style == SOLID) {
        surface = TTF_RenderText_Solid(
            font,
            text.c_str(),
            color
        );
    }

    else if (style == SHADED) {
        surface = TTF_RenderText_Shaded(
            font,
            text.c_str(),
            color,
            bg
        );
    }

    else if (style == BLENDED) {
        surface = TTF_RenderText_Blended(
            font,
            text.c_str(),
            color
        );
    }

    if (surface == nullptr) {
        SDL_Log("Erro ao renderizar texto: %s", TTF_GetError());
        return;
    }

    // Cria texture 
    texture = SDL_CreateTextureFromSurface(
        Game::GetInstance().GetRenderer(),
        surface
    );

    if (texture == nullptr) {
        SDL_Log("Erro ao criar texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    associated.box.setW(surface->w);
    associated.box.setH(surface->h);

    SDL_FreeSurface(surface);
}