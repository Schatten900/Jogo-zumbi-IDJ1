#include "game/game.h"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height){
    if (instance != nullptr) throw std::runtime_error("Game ja iniciado!");
    instance = this;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) throw std::runtime_error(SDL_GetError());

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    if (Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY,
        MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS,
        1024
    ) != 0) throw std::runtime_error(Mix_GetError());
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    state = new State();

}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Game& Game::GetInstance(){
    if (instance == nullptr) instance = new Game("Carlos Cauã Rocha da Silva - 231034304", 1200, 900);
    return *instance;
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

State& Game::GetState(){
    return *state;
}

void Game::Run(){
    State& state = GetState();
    int frameStart;
    float dt = 0;
    while (!state.QuitRequested()){
        frameStart = SDL_GetTicks();
        SDL_RenderClear(renderer);

        state.Update(dt);
        state.Render();
        SDL_RenderPresent(renderer);
        dt = (SDL_GetTicks() - frameStart) / 1000.0f;
        SDL_Delay(33);
    }
}


