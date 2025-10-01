#include "obstacle.h"
#include "raylib.h"
#include "constants.h"
#include <queue>

using namespace std;

Obstacle RecToObstacle(Rectangle target) { return {target}; }

Obstacle CreateObstacle(ScreenSide side,int width,int height){
    int spawnX = 0;

    switch(side){
        case Left:
            spawnX = 0;
            break;
        case Middle:
            spawnX = (SCREEN_WIDTH / 2) - (width / 2);
            break;
        case Right:
            spawnX = SCREEN_WIDTH - width;
            break;
        default:
            spawnX = 0;
            break;
    }
    
    Rectangle newRec = {spawnX, SCREEN_HEIGHT + height, width, height};

    return {newRec} ; 
}

Obstacle* GetObstacleFromQueue(queue<Obstacle> &obstacles, vector<Obstacle*> &obstaclesInScene){
    obstaclesInScene.push_back(&obstacles.front());
    obstacles.pop();

    return obstaclesInScene.back();
}

bool HasObstacleLeftScreen(Obstacle &obstacle){
    Vector2 obstacleCenter;

    obstacleCenter.x = obstacle.body.x + (obstacle.body.width / 2);
    obstacleCenter.y = obstacle.body.y - (obstacle.body.height / 2);

    if(obstacleCenter.x > (SCREEN_WIDTH - (obstacle.body.width / 2)) && obstacleCenter.x < (0 + (obstacle.body.width / 2))){
        return true;
    }

    if(obstacleCenter.y > (SCREEN_HEIGHT - (obstacle.body.height / 2)) && obstacleCenter.y < (0 + (obstacle.body.height / 2))){
        return true;
    }

    return false;
}

void UpdateAllObstacles(vector<Obstacle*> &obstaclesInScene){

    for (int i = 0; i < obstaclesInScene.size(); i++)
    {
        obstaclesInScene[i]->body.y -= obstaclesInScene[i]->moveSpeed;
    }
    


}