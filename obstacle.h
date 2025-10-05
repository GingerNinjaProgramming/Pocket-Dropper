#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <raylib.h>
#include <queue>
#include <player.h>
#include "enums.h"

using namespace std;

struct Obstacle{
    Rectangle body;
    int id;
    int moveSpeed = 1;
    bool hasEnteredScreen = false;
    bool hasHitPlayer = false;

    bool operator==(const Obstacle& other) {
        return body.x == other.body.x &&
           body.y == other.body.y &&
           body.width == other.body.width &&
           body.height == other.body.height &&
           moveSpeed == other.moveSpeed &&
           hasEnteredScreen == other.hasEnteredScreen;
    }

};

Obstacle RecToObstacle(Rectangle target);

Obstacle CreateObstacle(ScreenSide side,int width,int height);

Obstacle* GetObstacleFromQueue(queue<Obstacle> &obstacles,vector<Obstacle*> &obstaclesInScene);

bool HasObstacleLeftScreen(const Obstacle obstacle);

void UpdateAllObstacles(vector<Obstacle*> &obstaclesInScene, const Player &player);

#endif
