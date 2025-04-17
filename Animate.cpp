#include "Animate.h"

void Animation(sf::RectangleShape& objShape,const std::vector<sf::Texture> textures, int currentFrame) {
	objShape.setTexture(&textures[currentFrame]);
}