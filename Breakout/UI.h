#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "CONSTANTS.h"
#include "PowerupManager.h"
#include "ProgressBar.h"

class GameManager;

class UI
{
public:
	UI(sf::RenderWindow* window, sf::RenderTexture* screen, int lives, GameManager* gameManager);
	~UI();

	void updatePowerupText(std::pair<POWERUPS, float>);
	void updatePowerupBar(std::pair<POWERUPS, float>);
	float calculatePowerupBarHealth(float time);
	void lifeLost(int lives);
	void render();

private:
	ProgressBar* _powerupBar;

	GameManager* _gameManager;
	
	sf::RenderWindow* _window;
	sf::RenderTexture* _screen;
	sf::Font _font;
	sf::Text _powerupText;

	std::vector<sf::CircleShape> _lives;

	static constexpr float LIFE_RADIUS = 10.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};

