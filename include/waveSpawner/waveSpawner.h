#pragma once
#include "component/component.h"
#include "wave/wave.h"
#include "timer/timer.h"
#include <vector>

class WaveSpawner : public Component{

    public:
        WaveSpawner(GameObject& associated);
        //===========
        // Methods
        //===========
        void Update(float dt);
        void Render();
        void SpawnEnemy(bool spawnZombie);

        bool GetWaveFinished();

    private:

        //===========
        // Attributes
        //===========
        int zombieSpawned;
        int npcSpawned;

        std::vector<Wave> waves;
        int currentWave;

        bool waveFinished = false;

        //===========
        // Timer
        //===========
        Timer spawnTimer;
    

};