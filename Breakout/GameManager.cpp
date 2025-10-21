#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerup_spawn_odds(700), _shake(false), _shake_time(0.5f), _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f), _window_center(0.f, 0.f), _current_mouse_position(0.f, 0.f), _mouse_sensitivity(1.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    // NOTE: Set the mouse cursor to invisible to hide the fact it is being moved back into the center of the window every frame.
    _window->setMouseCursorVisible(false);
    _masterText.setString("");
    _levelComplete = false;
    _lives = 3;
    _shake = false;
    _shake_trigger_time = 0.f;

    _paddle = new Paddle(_window, &_screen);
    _brickManager = new BrickManager(_window, &_screen, this);
    _messagingSystem = new MessagingSystem(_window, &_screen);
    _ball = new Ball(_window, &_screen, 400.0f, this);
    _powerupManager = new PowerupManager(_window, &_screen, _paddle, _ball);
    _ui = new UI(_window, &_screen, _lives, this);

    // Create bricks
    _brickManager->createBricks(5, 8, 80.0f, 30.0f, 5.0f);

    // NOTE: Set the mouse the center of the window and set the window center variable to this initial mouse position.
    // This is not updated in the game loop as the window has been made to not be resizeable.
    _window->setPosition(sf::Vector2i(100.f, 100.f));
    sf::Mouse::setPosition(sf::Vector2i(_window->getSize().x / 2.f, _window->getSize().y / 2.f), *_window);
    _window_center = sf::Mouse::getPosition();
    loadShader();
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.\nPress Enter to Reply!");
        // NOTE: The player can freely move the mouse once the game is over - so they should be able to see it!
        _window->setMouseCursorVisible(true);
        manageReplyInput();
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.\nPress Enter to Reply!");
        _window->setMouseCursorVisible(true);
        manageReplyInput();
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
            _window->setMouseCursorVisible(true);
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
            _window->setMouseCursorVisible(false);
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;

    // NOTE: Count frame for shader
    _frame += 1;

    powerupSpawn(_powerup_spawn_odds);

    manageMouseInput(dt);

    sf::Mouse::setPosition(sf::Vector2i(500.f, 400.f), *_window);
    //_previous_mouse_position = _current_mouse_position;

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::powerupSpawn(int odds)
{
    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand() % odds == 0)
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }
}

void GameManager::manageMouseInput(float dt)
{
    // move paddle
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    _current_mouse_position = sf::Mouse::getPosition();


    if (_current_mouse_position.x == _window_center.x)
    {
        return;
    }

    if (_current_mouse_position.x > _window_center.x)
    {
        //_paddle->moveRight(dt * (_current_mouse_position.x - _previous_mouse_position.x));
        int movement_multiplier = (_current_mouse_position.x - _window_center.x) * _mouse_sensitivity;
        _paddle->moveRight(dt * movement_multiplier);
        return;
    }

    if (_current_mouse_position.x < _window_center.x)
    {
        //_paddle->moveLeft(dt * (_previous_mouse_position.x - _current_mouse_position.x));
        int movement_multiplier = (_window_center.x - _current_mouse_position.x) * _mouse_sensitivity;
        _paddle->moveLeft(dt * movement_multiplier);
        return;
    }

}

void GameManager::manageReplyInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        delete _paddle;
        delete _brickManager;
        delete _messagingSystem;
        delete _ball;
        delete _powerupManager;
        delete _ui;

        initialize();
    }
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    _shake = true;
    _shake_trigger_time = _time;
}

void GameManager::render()
{
    _screen.create(_window->getSize().x, _window->getSize().y);
    _screen.clear();

    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    //_window->draw(_masterText);
    _screen.draw(_masterText);
    _ui->render();

    _screen.display();
    // NOTE: Render texture has to be made into a sprite before it can be rendered to the window!
    sf::Sprite screen(_screen.getTexture());

    if (_shake == true && !_levelComplete && _lives > 0)
    {
        // Shaking the window instead of the screen due to the shader
        // Reference: https://en.sfml-dev.org/forums/index.php?topic=12159.msg84431#msg84431
        _window->setPosition(sf::Vector2i(100 + rand() % 25, 100 + rand() % 25));
        sf::Mouse::setPosition(sf::Vector2i(_window->getSize().x / 2.f, _window->getSize().y / 2.f), *_window);
        _window_center = sf::Mouse::getPosition();
        //screen.setPosition(sf::Vector2f(rand() % 25, rand() % 25));

        if (_time - _shake_trigger_time >= _shake_time)
        {
            _shake = false;
        }
    }

    if (_crt == true)
    {
        _shader.setUniform("u_time", _time);
        _shader.setUniform("u_frame", _frame);
        _window->draw(screen, &_shader);
    }
    else
    {
        _window->draw(screen);
    }
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::updateMouseSensitivity(float update)
{
    _mouse_sensitivity = std::clamp(_mouse_sensitivity += update, 0.1f, 2.0f);
}

void GameManager::loadShader()
{
    if (!_shader.loadFromFile("crt.frag", sf::Shader::Fragment)) {
        _crt = false;
        return;
    }

    // Reference: https://duerrenberger.dev/blog/2021/08/08/basic-fragment-shader-with-sfml/
    _shader.setUniform("u_resolution", sf::Glsl::Vec2{ _window->getSize()});

    _crt = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
