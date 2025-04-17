#include <SFML/Graphics.hpp>
#include "Animate.h"
#include "Game.h"

int main()
{
    int seed = time(0);
    srand(seed);

    ag::stateGame gameState;
    ag::initGame(gameState);

    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Apples game");

    sf::Clock gameClock;

    float lastTime = gameClock.getElapsedTime().asSeconds();

    // not work, say texture not exist
    //int totalFrames = 6;
    //float frameTime = 0.1f;
    //float elapsedTime = 0.f;

    while (window.isOpen())
    {
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        ag::checkStatusGame(gameState, deltaTime);

        // for animation
        //elapsedTime += deltaTime;
        //int currentFrame = (int(elapsedTime / frameTime) % totalFrames);
        //Animation(gameState.player.playerShape, gameState.player.playerArrTextures, currentFrame);

        ag::drawGame(gameState, window);
        
    }
}