#pragma once
#include <string>
#include "component/component.h"
#include "sprite/sprite.h"

class SpriteRenderer : public Component{
    public:
        //==============
        // Constructor
        //==============
        SpriteRenderer(GameObject& associated);
        SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);

        //==============
        // Methods
        //==============

        void Open(std::string file);
        void Update(float dt) override;
        void Render() override;

        //==============
        // Setters
        //==============
        void SetFrame(int frame);
        void SetCameraFollower(bool val);
        void SetFrameCount(int frameCountW, int frameCountH);

        void SetFrame(int frame, SDL_RendererFlip flip);
        void SetScale(float scaleX, float scaleY);
        void SetFlip(SDL_RendererFlip flip);

        //==============
        // Getters
        //==============
        Sprite& GetSprite();

    private:    
        Sprite sprite;
};