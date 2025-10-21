#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void manageMouseInput(float dt);
    void manageReplyInput();
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);
    void powerupSpawn(int m);
    void updateMouseSensitivity(float update);
    void loadShader();

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    int _frame = 0;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;
    int _powerup_spawn_odds;
    bool _shake;
    float _shake_time;
    float _shake_trigger_time;
    std::pair<POWERUPS, float> _powerupInEffect;
    // NOTE: Vector for tracking mouse position
    sf::Vector2i _window_center;
    sf::Vector2i _current_mouse_position;
    float _mouse_sensitivity;
    bool _crt;

    sf::Font _font;
    sf::Text _masterText;
    sf::RenderTexture _screen;
    sf::Shader _shader;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};
