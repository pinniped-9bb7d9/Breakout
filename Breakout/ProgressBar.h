#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include <vector>

// Reference: https://www.youtube.com/watch?v=2QOm8LgW0_Y
// Reference: https://en.sfml-dev.org/forums/index.php?topic=13066.0
// Reference: https://www.sfml-dev.org/documentation/3.0.2/classsf_1_1RectangleShape.html

class ProgressBar
{
public:
    ProgressBar(sf::RenderWindow* window, sf::RenderTexture* screen, float length, float height);
    virtual ~ProgressBar();

    void update(float dt);
    void render();

    void updateBarSize();

    void setBarFillColour(sf::Color colour);
    void setBarOutlineColour(sf::Color colour);
    void setBarOutlineThickness(float thickness);
    void setBarPosition(float x, float y);
    void setHealth(float health);

protected: 
    // Game logic
    float _health;

    // Render
    float _length; // length of the progress bar when it is full
    float _height; // height of the progress bar
    sf::RectangleShape _sprite;
    sf::Color _colour;
    sf::Color _outlineColour;
    sf::RenderWindow* _window;
    sf::RenderTexture* _screen;
};


