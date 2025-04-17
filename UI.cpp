#include "UI.h"
#include "Game.h"

namespace ag {

	sf::Font font("resources/winky.ttf");
	sf::Text scoreText(font, "hello");
	sf::Text gameOverText(font, "hello");

	void initUI() {
		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);

		gameOverText.setFont(font);
		gameOverText.setCharacterSize(48);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setStyle(sf::Text::Bold);
		gameOverText.setString("GAME OVER");
		gameOverText.setOrigin({ gameOverText.getLocalBounds().getCenter().x, gameOverText.getLocalBounds().getCenter().y });
		
	}

	void updateUI(stateUI& ui, const struct stateGame& game, float deltaTime) {
		scoreText.setString("Apple eats: " + std::to_string(game.eatCountApple));
		ui.stateGameOverText = game.isAlivePlayer;
	}

	void drawUI(stateUI& ui, sf::RenderWindow& window) {
		scoreText.setPosition({ 10.f, 10.f });
		window.draw(scoreText);

		if (!ui.stateGameOverText) {
			gameOverText.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f });
			window.draw(gameOverText);
		}
	}
}