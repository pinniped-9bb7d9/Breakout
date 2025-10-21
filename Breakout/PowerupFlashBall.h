#pragma once
#include "PowerupBase.h"
class PowerupFlashBall : public PowerupBase
{
public:
    PowerupFlashBall(sf::RenderWindow* window, sf::RenderTexture* screen, Paddle* paddle, Ball* ball);
    ~PowerupFlashBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect


};



