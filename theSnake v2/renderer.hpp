#pragma once
#include <SFML/Graphics.hpp>
#include "snake.hpp"


class Renderer 
{
private:

	sf::RectangleShape m_rendererCell;


public:

	Renderer();
	~Renderer();

	void render(sf::RenderWindow& mainWindow, Snake& snakeObjHandler, sf::Vector2i foodPosition);
	
	
private:

	void drawBackground(sf::RenderWindow& mainWindow);
	void drawFood(sf::RenderWindow& mainWindow, sf::Vector2i foodPosition);
	void drawSnake(sf::RenderWindow& mainWindow, Snake& snakeObjHandler);

};