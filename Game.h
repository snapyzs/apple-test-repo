#pragma once
#include "Player.h"
#include "Apple.h"
#include "UI.h"

namespace ag {

    struct stateGame {
        Player player;
        Apple* apple;
        bool isAlivePlayer = true;
        float timeSinceGameOver = 0.f;
        int randomApple = float(rand()) / RAND_MAX * 50;
        int eatCountApple = 0;
        stateUI ui;
        uint32_t gameModeRun = 0;
        enum gameMode {
            doneApple = 1 << 0, // 0
            infApple = 1 << 1, // 1
            speedPlayer = 1 << 2 // 2
        };
    };

    void initGame(stateGame& game);
    void drawGame(stateGame& game, sf::RenderWindow& window);
    void checkStatusGame(stateGame& game, float& deltaTime);
}