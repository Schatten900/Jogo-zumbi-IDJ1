#include "player/player.h"


Player::Player(float x, float y){
    pos = {x,y};
    vel = {0,0};
    speed = 200.0f;
}

void Player::update(float dt){
    pos = pos + (vel * dt);
}