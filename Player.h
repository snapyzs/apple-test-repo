#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Consts.h"

namespace ag {

    struct Player {
        position2d playerPosition;
        float playerSpeed = SPEED_PLAYER;
        sf::Texture texturePlayer;
        sf::RectangleShape playerShape;
        std::vector<sf::Texture> playerArrTextures;
        sf::Music soundEat;
        sf::Music soundDead;
    };

    void initPlayer(Player& player);
}