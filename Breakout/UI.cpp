#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

UI::UI(sf::RenderWindow* window, sf::RenderTexture* screen, int lives, GameManager* gameManager) 
	: _window(window), _screen(screen), _gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Red);	
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(2.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition(((LIFE_RADIUS*2 + LIFE_PADDING) * i) + 100.f, LIFE_PADDING*3);
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(700, 60);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	_powerupBar = new ProgressBar(window, screen, 150.F, 20.F);
	_powerupBar->setBarFillColour(sf::Color::White);
	_powerupBar->setBarOutlineColour(sf::Color::Cyan);
	_powerupBar->setBarOutlineThickness(2.F);
	_powerupBar->setBarPosition(700.F, 60.F);
}

UI::~UI()
{
	delete _powerupBar;
	_powerupBar = nullptr;
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	switch (powerup.first)
	{
	case bigPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		break;
	case flashBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("flash " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case none:
		_powerupText.setString("");
	}
}

void UI::updatePowerupBar(std::pair<POWERUPS, float> powerup)
{
	if (powerup.first == none)
	{
		_powerupBar->setHealth(0.f);
		return;
	}

	_powerupBar->setHealth(calculatePowerupBarHealth(powerup.second));

	switch (powerup.first)
	{
	case bigPaddle:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		//_powerupText.setString("big " + oss.str());
		//_powerupText.setFillColor(paddleEffectsColour);

		_powerupBar->setBarFillColour(paddleEffectsColour);
		break;
	case smallPaddle:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		//_powerupText.setString("small " + oss.str());
		//_powerupText.setFillColor(paddleEffectsColour);

		_powerupBar->setBarFillColour(paddleEffectsColour);
		break;
	case slowBall:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		//_powerupText.setString("slow " + oss.str());
		//_powerupText.setFillColor(ballEffectsColour);

		_powerupBar->setBarFillColour(ballEffectsColour);
		break;
	case fastBall:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		//_powerupText.setString("fast " + oss.str());
		//_powerupText.setFillColor(ballEffectsColour);

		_powerupBar->setBarFillColour(ballEffectsColour);
		break;
	case fireBall:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		//_powerupText.setString("fire " + oss.str());
		//_powerupText.setFillColor(extraBallEffectsColour);

		_powerupBar->setBarFillColour(extraBallEffectsColour);
		break;
	case flashBall:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		//_powerupText.setString("flash " + oss.str());
		//_powerupText.setFillColor(ballEffectsColour);

		_powerupBar->setBarFillColour(extraBallEffectsColour);
		break;
	}

	_powerupBar->updateBarSize();
}

float UI::calculatePowerupBarHealth(float time)
{
	float health;

	health = std::clamp(time / POWERUP_DURATION, 0.0f, 1.0f);

	return health;
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	//_window->draw(_powerupText);
	_screen->draw(_powerupText);

	_powerupBar->render();

	for (sf::CircleShape life : _lives)
	{
		//_window->draw(life);
		_screen->draw(life);
	}
}