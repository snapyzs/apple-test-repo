#include "Game.h"

namespace ag {

    void initGame(stateGame& game) {
        initPlayer(game.player);
        initUI();

        for (int i = 0; i < APPLE_COUNT; i++) {
            initApple(game.apple[i]);
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
        for (int i = 0; i < APPLE_COUNT; i++) {
            game.apple[i].appleArray.setPosition({ getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).x, getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).y });
        }
    }

    void checkStatusGame(stateGame& game, float& deltaTime) {
        if (!game.isAlivePlayer) {
            if (game.timeSinceGameOver <= PAUSE_TIME) {
                game.timeSinceGameOver += deltaTime;
            }
            else {
                game.isAlivePlayer = true;
                restartGame(game);
            }
        } else {
            updateGame(game, deltaTime);
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

    void drawGame(stateGame& game, sf::RenderWindow& window) {

        window.clear();
        window.draw(game.player.playerShape);

        for (int i = 0; i < APPLE_COUNT; i++) {
            if (!game.apple[i].isCollision) {
                if (checkCollision(game.player.playerShape.getPosition().x, game.player.playerShape.getPosition().y, game.apple[i].appleArray.getPosition().x, game.apple[i].appleArray.getPosition().y, PLAYER_SIZE, APPLE_SIZE)) {
                    game.apple[i].appleArray.setPosition({ getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).x, getRandomPosition(SCREEN_WIDTH,SCREEN_HEIGHT).y });
                    if (i % 2 == 0) {
                        game.apple[i].appleArray.setTexture(&game.apple[i].textureAppleGreen);
                    }
                    game.player.playerSpeed += PLAYER_BOOST;
                    game.eatCountApple++;
                    game.player.soundEat.play();
                }
                window.draw(game.apple[i].appleArray);
            }
        }

        drawUI(game.ui, window);

        window.display();
    }
}