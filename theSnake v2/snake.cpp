#pragma once
#include "snake.hpp"
#include "config.hpp"
#include <random>


Snake::Snake() {}
Snake::~Snake() {}


void Snake::spawn()
{
    clearCoordinates();
    addCoordinate(sf::Vector2i(config::cols / 2, config::rows / 2));
    setRandomDirection();
}

const std::deque<sf::Vector2i>& Snake::getCoordinates()
{
    return m_dCoordinates;
}

void Snake::addCoordinate(sf::Vector2i coordinate)
{
    m_dCoordinates.push_back(coordinate);
}

void Snake::clearCoordinates()
{
    m_dCoordinates.clear();
}

void Snake::setRandomDirection()
{
    std::mt19937 seed(std::random_device{}());
    std::uniform_int_distribution dist(1, 4);
    int directionIndex = dist(seed);

    switch (directionIndex)
    {
    case 1:
        setDirection(sf::Vector2i(0, -1));
        break;
    case 2:
        setDirection(sf::Vector2i(0, 1));
        break;
    case 3:
        setDirection(sf::Vector2i(-1, 0));
        break;
    case 4:
        setDirection(sf::Vector2i(1, 0));
        break;
    default:
        setDirection(sf::Vector2i(0, 0));
        break;
    }
}

void Snake::setDirection(sf::Vector2i direction)
{
    m_direction = direction;
}

const sf::Vector2i Snake::getDirection()
{
    return m_direction;
}

const bool Snake::isColliding(sf::Vector2i coordinate)
{
    for (unsigned int i = 0; i < m_dCoordinates.size(); i++) {
        if (m_dCoordinates[i] == coordinate)
            return true;
    }
    return false;
}

void Snake::move(sf::Vector2i nextPosition)
{
    m_dCoordinates.push_front(nextPosition);
    m_dCoordinates.pop_back();
}