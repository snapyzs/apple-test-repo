#pragma once
#include <SFML/Graphics.hpp>
#include "Consts.h"



namespace ag {

	struct stateUI {
		bool stateGameOverText = false;
	};

	// in SFML 3 not exist default constructor sf::Text, and can't use in struct stateUI 
	void initUI();
	void updateUI(stateUI& ui, const struct stateGame& game, float deltaTime);
	void drawUI(stateUI& ui, sf::RenderWindow& window);
}