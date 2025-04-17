#pragma once
#include "Player.h"
#include "Apple.h"
#include "UI.h"

namespace ag {

    struct stateGame {
        Player player;
        Apple apple[APPLE_COUNT];
        bool isAlivePlayer = true;
        float timeSinceGameOver = 0.f;
        int eatCountApple = 0;
        stateUI ui;
    };

    void initGame(stateGame& game);
    void gameOver(stateGame& game);
    void updateGame(stateGame& game, float& deltaTime);
    void drawGame(stateGame& game, sf::RenderWindow& window);
    void restartGame(stateGame& game);
    void checkStatusGame(stateGame& game, float& deltaTime);
}