#include "component/component.h"    
#include <string>
#include <SDL2/SDL_ttf.h>

class Text : public Component {

    public:


        //=================
        //  Enums
        //=================
        enum TextStyle { SOLID, SHADED, BLENDED};

        //==============
        //  Constructor
        //==============
        
        Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
        ~Text();

        //==============
        //  Methods
        //==============
        void Update(float dt);
        void Render();


        //=================
        //  Setters
        //=================
        void SetText(std::string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(std::string fontFile);
        void SetFontSize(int fontSize);

        void RemakeTexture();


    private:
        TTF_Font* font;
        SDL_Texture* texture;
        std::string text;
        TextStyle style;
        std::string fontFile;
        int fontSize;
        SDL_Color color;

};