#include "waveSpawner/waveSpawner.h"
#include "gameObject/gameObject.h"
#include "zombie/zombie.h"
#include "aicontroller/aiController.h"
#include "game/game.h"
#include "character/character.h"
#include <cstdlib>
#include <ctime>
#include "gameData/gameData.h"
#include "endState/endState.h"
#include <algorithm>

WaveSpawner::WaveSpawner(GameObject& associated)
    : Component(associated),
      zombieSpawned(0),
      npcSpawned(0),
      currentWave(0)
{
    spawnTimer.Restart();


    for (int i = 0; i < 5; i++){
        int zombies = 3 + i * 2;
        int npcs = 1 + i; 

        float cooldown = std::max(0.3f, 1.5f - i * 0.08f);

        waves.emplace_back(zombies, npcs, cooldown);
    }
}

void WaveSpawner::Update(float dt){
    spawnTimer.Update(dt);

    if (currentWave >= (int)waves.size()){
        associated.RequestDelete();
        GameData::playerVictory = true;
        Game::GetInstance().Push(new EndState());
        Game::GetInstance().GetCurrentState().SetPopRequested(true);
        return;
    }

    Wave& wave = waves[currentWave];

    auto playerGO = Character::player.lock();
    if (!playerGO) return;

    //===================
    // Enemy
    //===================
    if (spawnTimer.Get() > wave.cooldown){
        if (zombieSpawned < wave.zombies){
            SpawnEnemy(true);
            zombieSpawned++;
        }
        else if (npcSpawned < wave.npcs){
            SpawnEnemy(false);
            npcSpawned++;
        }

        spawnTimer.Restart();
    }

    //===================
    // Controll
    //===================
    if (zombieSpawned >= wave.zombies && npcSpawned >= wave.npcs){
        if (Zombie::zombieCount == 0 && AiController::npcCounter == 0){
            currentWave++;
            zombieSpawned = 0;
            npcSpawned = 0;
            spawnTimer.Restart();
        }
    }
}

void WaveSpawner::Render(){}

void WaveSpawner::SpawnEnemy(bool spawnZombie){

    auto playerGO = Character::player.lock();
    if (!playerGO) return;

    Vec2 playerPos = playerGO->box.getCenter();

    //===================
    // SPAWN 
    //===================
    Vec2 spawnPos;
    do {
        int x = playerPos.getX() + ((rand() % 800) - 400);
        int y = playerPos.getY() + ((rand() % 800) - 400);

        x = std::max(0, x);
        y = std::max(0, y);

        x = std::min(x, 1200);
        y = std::min(y, 900);

        spawnPos = Vec2(x,y);
    } while (spawnPos.distance(playerPos) < 200);

    auto go = std::make_shared<GameObject>();
    go->box = Rect(spawnPos.getX(), spawnPos.getY(), 64, 64);

    if (spawnZombie){
        go->AddComponent(new Zombie(*go));
    } else {
        go->AddComponent(new AiController(*go));
    }

    Game::GetInstance().GetCurrentState().AddObject(go);
}

bool WaveSpawner::GetWaveFinished(){
    return waveFinished;
}