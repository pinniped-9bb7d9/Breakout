#include "ProgressBar.h"

ProgressBar::ProgressBar(sf::RenderWindow* window, sf::RenderTexture* screen, float length, float height)
	: _health(1.f), _length(length), _height(height), _window(window), _screen(screen)
{
}

ProgressBar::~ProgressBar()
{

}

auto ProgressBar::update(float dt) -> void
{

}

auto ProgressBar::updateBarSize() -> void
{
	_sprite.setSize(sf::Vector2f(_health * _length, _height));
}

auto ProgressBar::render() -> void
{
	if (_health <= 0.0f)
	{
		return;
	}

	_screen->draw(_sprite);
}

auto ProgressBar::setBarFillColour(sf::Color colour) -> void
{
	_sprite.setFillColor(colour);
}

auto ProgressBar::setBarOutlineColour(sf::Color colour) -> void
{
	_sprite.setOutlineColor(colour);
}

auto ProgressBar::setBarOutlineThickness(float thickness) -> void
{
	_sprite.setOutlineThickness(thickness);
}

auto ProgressBar::setBarPosition(float x, float y) -> void
{
	_sprite.setPosition(x, y);
}

auto ProgressBar::setHealth(float health) -> void
{
	_health = health;
}