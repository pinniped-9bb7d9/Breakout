#include "PowerupFireBall.h"


PowerupFireBall::PowerupFireBall(sf::RenderWindow* window, sf::RenderTexture* screen, Paddle* paddle, Ball* ball)
    : PowerupBase(window, screen, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupFireBall::~PowerupFireBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }

    // NOTE: Removed memory leak
    delete pInteger;
    pInteger = nullptr;
    
}

std::pair<POWERUPS, float> PowerupFireBall::applyEffect()
{
    _ball->setFireBall(5.0f);
    return { fireBall, 5.0f };
}