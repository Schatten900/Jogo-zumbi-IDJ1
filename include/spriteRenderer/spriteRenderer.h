#pragma once
#include <string>
#include "component/component.h"
#include "sprite/sprite.h"

class SpriteRenderer : public Component{
    public:
        SpriteRenderer(GameObject& associated);
        SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);
        void Open(std::string file);
        void SetFrameCount(int frameCountW, int frameCountH);
        void Update(float dt) override;
        void Render() override;
        void SetFrame(int frame);

        void SetCameraFollower(bool val);


    private:    
        Sprite sprite;
};