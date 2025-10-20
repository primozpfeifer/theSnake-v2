#pragma once
#include <SFML/Graphics.hpp>
#include <deque>


class Snake
{
private:

	std::deque<sf::Vector2i> m_dCoordinates;
	sf::Vector2i m_direction;


public:

	Snake();
	~Snake();

	void spawn();
	const std::deque<sf::Vector2i>& getCoordinates();
	void addCoordinate(sf::Vector2i coordinate);
	void clearCoordinates();
	void setRandomDirection();
	void setDirection(sf::Vector2i direction);
	const sf::Vector2i getDirection();
	const bool isColliding(sf::Vector2i coordinate);
	void move(sf::Vector2i nextPosition);

};