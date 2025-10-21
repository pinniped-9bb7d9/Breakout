#include "PowerupFlashBall.h"

PowerupFlashBall::PowerupFlashBall(sf::RenderWindow* window, sf::RenderTexture* screen, Paddle* paddle, Ball* ball)
    : PowerupBase(window, screen, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupFlashBall::~PowerupFlashBall()
{
}

std::pair<POWERUPS, float> PowerupFlashBall::applyEffect()
{
    _ball->setVelocity(3.f, 7.5f);
    return { fastBall, 5.0f };
}