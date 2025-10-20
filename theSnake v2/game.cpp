#pragma once
#include "game.hpp"
#include "config.hpp"
#include <random>


Game::Game()
{
    m_mainWindow.create(
        sf::VideoMode(config::cols * static_cast<int>(config::cellSize), config::rows * static_cast<int>(config::cellSize)),
        "the SNAKE v2",
        sf::Style::Titlebar | sf::Style::Close);
    m_mainWindow.setKeyRepeatEnabled(false);
    m_mainWindow.setFramerateLimit(60);
}

Game::~Game() {}


// main game loop

void Game::run()
{
    restart();

    while (m_mainWindow.isOpen())
    {
        checkEvents();
        update();
        renderer.render(m_mainWindow, m_snake, m_foodPosition);
    }
}


// auxiliary methods

void Game::restart()
{
    m_snake.spawn();
    spawnFood();
    m_gameTimer.restart();
}

void Game::spawnFood()
{
    std::mt19937 seed(std::random_device{}());
    sf::Vector2i coordinate = m_snake.getCoordinates()[0];

    while (m_snake.isColliding(coordinate))
    {
        std::uniform_int_distribution distX(1, config::cols - 2);
        std::uniform_int_distribution distY(1, config::rows - 2);
        coordinate = sf::Vector2i(distX(seed), distY(seed));
    }
    m_foodPosition = coordinate;
}


// event (input) system

void Game::checkEvents()
{
    sf::Event event;

    while (m_mainWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_mainWindow.close();
            return;
        
        case sf::Event::KeyPressed:
            m_lastPressedKey = event.key.code;
            break;
        }
    }
}


// game logic

void Game::update()
{
    // quit if escape key pressed
    if (m_lastPressedKey == sf::Keyboard::Escape)
    {
        m_mainWindow.close();
        return;
    }

    // game speed timer check
    if (m_gameTimer.getElapsedTime().asMilliseconds() < config::gameTimerTick)
        return;


    sf::Vector2i direction = sf::Vector2i(0, 0);

    switch (m_lastPressedKey)
    {
    case sf::Keyboard::Up:
        direction = sf::Vector2i(0, -1);
        break;

    case sf::Keyboard::Down:
        direction = sf::Vector2i(0, 1);
        break;

    case sf::Keyboard::Left:
        direction = sf::Vector2i(-1, 0);
        break;

    case sf::Keyboard::Right:
        direction = sf::Vector2i(1, 0);
        break;
    }
    m_lastPressedKey = sf::Keyboard::Unknown;


    // snake reversing and direction checks
    if (m_snake.getDirection() + direction == sf::Vector2i(0, 0) || direction == sf::Vector2(0, 0))
        direction = m_snake.getDirection();
    else
        m_snake.setDirection(direction);
    

    sf::Vector2i nextPosition = m_snake.getCoordinates()[0] + direction;


    // snake self collision
    // second expression allows head to move to tail end's previous position (2x2 square move)
    if (m_snake.isColliding(nextPosition) && nextPosition != m_snake.getCoordinates()[m_snake.getCoordinates().size() - 1])
    {
        //gameover = true;
        m_mainWindow.close();
        return;
    }

    // border collision
    else if (nextPosition.x == 0 || nextPosition.x == config::cols - 1 || nextPosition.y == 0 || nextPosition.y == config::rows - 1)
    {
        //gameover = true;
        m_mainWindow.close();
        return;
    }

    // food collision
    else if (nextPosition == m_foodPosition)
    {
        m_snake.addCoordinate(nextPosition);
        spawnFood();
    }

    // move the snake to new position
    m_snake.move(nextPosition);


    m_gameTimer.restart();
}