#include "Player.h"
#include "Animate.h"

namespace ag {

    void initPlayer(Player& player) {
        player.playerPosition = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
        player.playerSpeed = SPEED_PLAYER;
        player.texturePlayer.loadFromFile("resources/pacman.png");

        player.soundEat.openFromFile("resources/apple.mp3");
        player.soundDead.openFromFile("resources/wall.mp3");

        for (int i = 1; i < 7;i++) {
            sf::Texture texture;
            texture.loadFromFile("resources/pacman_anim/pacman" + std::to_string(i) + ".png");
            player.playerArrTextures.push_back(texture);
        }

        player.playerShape.setTexture(&player.texturePlayer);
        player.playerShape.setSize({ PLAYER_SIZE, PLAYER_SIZE });
        player.playerShape.setOrigin({ PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f });
        player.playerShape.setPosition({ player.playerPosition.x, player.playerPosition.y });
    }
}