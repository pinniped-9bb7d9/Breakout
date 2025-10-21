#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <iostream>

int main()
{
    // TODO: Should I set the window width and hieght in seperate variables to avoid magic variables?
    // NOTE: Set the window size to be fixed as resizes the window causes issues for input and physics.
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout", sf::Style::Titlebar | sf::Style::Close);
    //window.setSize(sf::Vector2u(1000, 800));
    GameManager gameManager(&window);
    gameManager.initialize();

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            } 
            
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                int update = event.mouseWheelScroll.delta;
                gameManager.updateMouseSensitivity(static_cast<float>(update) * 0.1f);
            }
        }

        deltaTime = clock.restart().asSeconds();

        gameManager.update(deltaTime);

        window.clear();
        gameManager.render();
        window.display();
    }

    return 0;
}
