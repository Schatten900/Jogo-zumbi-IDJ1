#include "game/game.h"
#include "resources/resources.h"
#include "inputManager/inputManager.h"
#include "camera/camera.h"

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

    if (TTF_Init() != 0)
        throw std::runtime_error(TTF_GetError());

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
    storedState = nullptr;
    frameStart = SDL_GetTicks();

}

Game::~Game(){

    while(!stateStack.empty()){
        stateStack.pop();
    }
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearImages();
    Resources::ClearFonts();


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
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

State& Game::GetCurrentState(){
    return *stateStack.top();
}

void Game::Push(State* state){
    storedState = state;
}

void Game::Run(){
    
    if (storedState == nullptr) return;

    stateStack.push(std::unique_ptr<State>(storedState));
    storedState = nullptr;

    stateStack.top()->Start();

    while (!stateStack.empty() && !stateStack.top()->QuitRequested()){


        CalculateDeltaTime();

        InputManager::GetInstance().Update();

        SDL_RenderClear(renderer);

        if (stateStack.top()->PopRequested()){
            stateStack.pop();

            if (!stateStack.empty()){
                stateStack.top()->Resume();
            }
        }

        if (storedState != nullptr){

            if (!stateStack.empty()){
                stateStack.top()->Pause();
            }

            stateStack.push(std::unique_ptr<State>(storedState));

            storedState = nullptr;

            stateStack.top()->Start();
        }

        stateStack.top()->Update(dt);
        stateStack.top()->Render();

        SDL_RenderPresent(renderer);
    }

    Resources::ClearFonts();
    Resources::ClearImages();
    Resources::ClearSounds();
    Resources::ClearMusics();
}

void Game::CalculateDeltaTime(){

    frameStart = SDL_GetTicks(); 

    int frameTime = SDL_GetTicks() - frameStart;

    if (frameTime < 33)
        SDL_Delay(33 - frameTime);

    dt = (SDL_GetTicks() - frameStart) / 1000.0f;
}

float Game::GetDeltaTime(){
    return dt;
}

