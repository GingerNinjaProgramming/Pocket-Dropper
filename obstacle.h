#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <raylib.h>
#include <queue>
#include "enums.h"

using namespace std;

struct Obstacle{
    Rectangle body;
    int moveSpeed = 10;
};

Obstacle RecToObstacle(Rectangle target);

Obstacle CreateObstacle(ScreenSide side,int width,int height);

Obstacle* GetObstacleFromQueue(queue<Obstacle> &obstacles,vector<Obstacle*> &obstaclesInScene);

bool HasObstacleLeftScreen(Obstacle &obstacle);

void UpdateAllObstacles(vector<Obstacle*> &obstaclesInScene);

#endif
