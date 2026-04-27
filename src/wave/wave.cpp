#include "wave/wave.h"

Wave::Wave(int zombies, int npcs, float cooldown){
    this->zombies = zombies;
    this->npcs = npcs;
    this->cooldown = cooldown;
}