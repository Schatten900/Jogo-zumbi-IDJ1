#include <SDL2/SDL.h>
#include "game/game.h"
#include "titleState/titleState.h"

int main (int argc, char** argv){
    Game& game = Game::GetInstance();
    game.Push(new TitleState());
    game.Run();
    return 0;
}