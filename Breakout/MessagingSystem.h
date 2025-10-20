// DEPRECATED

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class MessagingSystem
{
public:
	MessagingSystem(sf::RenderWindow* window, sf::RenderTexture* screen);
	~MessagingSystem();

	void update(float dt);
	void render();
	
	void setMessage(std::string message, float timeToDisplay);

private:

	sf::RenderWindow* _window;
	sf::RenderTexture* _screen;

	sf::Text _message;
	sf::Font _font;
	float _messageTimer = 0.f;
	float _timeToDisplay = 0.f;
};

