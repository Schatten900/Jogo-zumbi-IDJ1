#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include "game/game.h"

int main (int argc, char** argv){
    Game& game = Game::GetInstance();
    game.Run();
    return 0;
}