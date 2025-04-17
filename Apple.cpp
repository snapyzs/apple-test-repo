#include "Apple.h"

namespace ag {

    void initApple(Apple& apple) {
        apple.appleArray.setRadius(APPLE_SIZE);
        apple.textureAppleRed.loadFromFile("resources/apple_red.png");
        apple.textureAppleGreen.loadFromFile("resources/apple_green.png");
        apple.appleArray.setTexture(&apple.textureAppleRed);
        apple.appleArray.setOrigin({ APPLE_SIZE / 2.f, APPLE_SIZE / 2.f });
        apple.appleArray.setPosition({ getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).x, getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).y });
        apple.isCollision = false;
    }
}