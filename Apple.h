#pragma once
#include <SFML/Graphics.hpp>
#include "Consts.h"
#include "Math.h"

namespace ag {

    struct Apple {
        sf::CircleShape appleArray;
        bool isCollision = false;
        sf::Texture textureAppleRed;
        sf::Texture textureAppleGreen;
    };


    void initApple(Apple& apple);
}