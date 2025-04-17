#include "Game.h"
#include <iostream>

namespace ag {

    void initGame(stateGame& game) {
        initPlayer(game.player);
        
        game.apple = new Apple[game.randomApple];

        for (int i = 0; i < game.randomApple; i++) {
            initApple(game.apple[i]);
        }

        initUI();
    }

    void changeAppleGameMode(stateGame& game,int count) {
        delete[] game.apple;
        game.randomApple = count;
        game.apple = new Apple[count];
        for (int i = 0; i < count; i++) {
            initApple(game.apple[i]);
        }
        game.ui.gameMode = true;
    }
    
    void gameMode(stateGame& game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            game.gameModeRun |= static_cast<uint32_t>(stateGame::doneApple);
            changeAppleGameMode(game,20);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            game.gameModeRun |= static_cast<uint32_t>(stateGame::infApple);
            changeAppleGameMode(game, 30);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            game.gameModeRun |= static_cast<uint32_t>(stateGame::speedPlayer) | static_cast<uint32_t>(stateGame::infApple);
            changeAppleGameMode(game, 50);
        }
    }

    void gameOver(stateGame& game) {
        game.isAlivePlayer = false;
        game.player.soundDead.play();
        game.timeSinceGameOver = 0.f;
    }

    void restartGame(stateGame& game) {
        game.player.playerShape.setPosition({ game.player.playerPosition.x, game.player.playerPosition.y });
        game.player.playerSpeed = SPEED_PLAYER;
        game.eatCountApple = 0;
        for (int i = 0; i < game.randomApple; i++) {
            game.apple[i].appleArray.setPosition({ getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).x, getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).y });
        }
    }

    void updateGame(stateGame& game, float& deltaTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            game.player.playerShape.move({ 0.f, game.player.playerSpeed * deltaTime });
            game.player.playerShape.setRotation(sf::degrees(90));
            game.player.playerShape.setScale({ 1.f, 1.f });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            game.player.playerShape.move({ 0.f, -game.player.playerSpeed * deltaTime });
            game.player.playerShape.setRotation(sf::degrees(270));
            game.player.playerShape.setScale({ 1.f, 1.f });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            game.player.playerShape.move({ game.player.playerSpeed * deltaTime, 0.f });
            game.player.playerShape.setRotation(sf::degrees(0));
            game.player.playerShape.setScale({ 1.f, 1.f });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            game.player.playerShape.move({ -game.player.playerSpeed * deltaTime, 0.f });
            game.player.playerShape.setRotation(sf::degrees(0));
            game.player.playerShape.setScale({ -1.f, 1.f });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
            restartGame(game);
        }

        if (game.player.playerShape.getPosition().x - PLAYER_SIZE / 2.f < 0.f || game.player.playerShape.getPosition().x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
            game.player.playerShape.getPosition().y - PLAYER_SIZE / 2.f < 0.f || game.player.playerShape.getPosition().y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT) {
            gameOver(game);
        }

        updateUI(game.ui, game, deltaTime);

    }

    void checkStatusGame(stateGame& game, float& deltaTime) {
        if (!game.ui.gameMode) {
            gameMode(game);
        } else {
            if (!game.isAlivePlayer) {
                if (game.timeSinceGameOver <= PAUSE_TIME) {
                    game.timeSinceGameOver += deltaTime;
                }
                else {
                    game.isAlivePlayer = true;
                    restartGame(game);
                }
            }
            else {
                updateGame(game, deltaTime);
            }
        }
    }


    void gameModeRunning(stateGame& game, sf::RenderWindow& window) {
        for (int i = 0; i < game.randomApple; i++) {
            if (i % 2 == 0) {
                game.apple[i].appleArray.setTexture(&game.apple[i].textureAppleGreen);
            }
            if (!game.apple[i].isCollision) {
                if (checkCollision(game.player.playerShape.getPosition().x, game.player.playerShape.getPosition().y, game.apple[i].appleArray.getPosition().x, game.apple[i].appleArray.getPosition().y, PLAYER_SIZE, APPLE_SIZE)) {
                    if (game.gameModeRun & static_cast<uint32_t>(stateGame::infApple)) {
                        game.apple[i].appleArray.setPosition({ getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).x, getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).y });
                    }
                    if (game.gameModeRun & static_cast<uint32_t>(stateGame::doneApple)) {
                        game.apple[i].appleArray.setPosition({ -50.f, -50.f });
                    }
                    if (game.gameModeRun & static_cast<uint32_t>(stateGame::speedPlayer) && game.gameModeRun & static_cast<uint32_t>(stateGame::infApple)) {
                        game.player.playerSpeed += PLAYER_BOOST;
                    }
                    game.eatCountApple++;
                    game.player.soundEat.play();
                }
                window.draw(game.apple[i].appleArray);
            }
        }
    }

    void drawGame(stateGame& game, sf::RenderWindow& window) {

        window.clear();
        window.draw(game.player.playerShape);

        gameModeRunning(game, window);

        drawUI(game.ui, window);

        window.display();
    }
}