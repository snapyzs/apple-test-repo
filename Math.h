#pragma once


struct position2d {
    float x = 0;
    float y = 0;
};

bool checkCollision(float playerX, float playerY, float appleX, float appleY, float playerSize, float appleSize);

position2d getRandomPosition(float screenW, float sreenH);