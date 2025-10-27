#include "PowerupSlowBall.h"

PowerupSlowBall::PowerupSlowBall(sf::RenderWindow* window, sf::RenderTexture* screen, Paddle* paddle, Ball* ball)
    : PowerupBase(window, screen, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour); 
}

PowerupSlowBall::~PowerupSlowBall()
{
}

std::pair<POWERUPS, float> PowerupSlowBall::applyEffect()
{
    _ball->setVelocity(0.5f, 5.0f);
    return { slowBall, POWERUP_DURATION };
}