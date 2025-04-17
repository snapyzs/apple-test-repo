#include "UI.h"
#include "Game.h"

namespace ag {

	sf::Font font("resources/winky.ttf");
	sf::Text scoreText(font, "Apple eats:");
	sf::Text gameOverText(font, "GAME OVER");
	sf::Text gameModeText(font, "");

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
		
		gameModeText.setFont(font);
		gameModeText.setCharacterSize(24);
		gameModeText.setString("Use mode game: 1 - 20 apples, apple will done \n2 - 30 apples, infinity apple \n3 - 50 apples, infinity apple and speed up per eat\nuse number on keyboard");
		gameModeText.setFillColor(sf::Color::White);
		gameModeText.setPosition({ 100.f , 100.f });

	}

	void updateUI(stateUI& ui, const struct stateGame& game, float deltaTime) {
		scoreText.setString("Apple eats: " + std::to_string(game.eatCountApple));
		ui.stateGameOverText = game.isAlivePlayer;
	}

	void drawUI(stateUI& ui, sf::RenderWindow& window) {
		scoreText.setPosition({ 10.f, 10.f });
		window.draw(scoreText);

		if (!ui.stateGameOverText && ui.gameMode) {
			gameOverText.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f });
			window.draw(gameOverText);
		}

		if (!ui.gameMode) {
			window.draw(gameModeText);
		}
	}
}