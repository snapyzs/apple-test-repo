#include "Math.h"
#include <cstdlib>

bool checkCollision(float playerX, float playerY, float appleX, float appleY, float playerSize, float appleSize) {
    float deltaX = playerX - appleX;
    float deltaY = playerY - appleY;
    float dist = float(sqrt(deltaX * deltaX + deltaY * deltaY));
    return dist < (playerSize + appleSize) / 2.f;
}

position2d getRandomPosition(float screenW, float screenH) {
    position2d randPosition;
    randPosition.x = float(rand()) / RAND_MAX * screenW;
    randPosition.y = float(rand()) / RAND_MAX * screenH;
    return randPosition;
}