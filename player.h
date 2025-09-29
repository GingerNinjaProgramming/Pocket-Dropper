#ifndef PLAYER_H
#define PLAYER_H

struct Player{
    float x,y;
};

Player CreatePlayer();

void DrawPlayer(const Player &player);

#endif