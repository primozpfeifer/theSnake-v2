#pragma once


namespace config
{
	inline const int cols = 19;
	inline const int rows = 19;
	inline const float cellSize = 40.0f;
	inline const float cellOutlineThickness = 0.5f;

	inline const int gameTimerTick = 300;

}

namespace colors
{
	inline const sf::Color outline(0, 0, 0);
	inline const sf::Color border(32, 32, 32);
	inline const sf::Color empty(37, 36, 86);
	inline const sf::Color food(76, 187, 23);
	inline const sf::Color snakeHead(153, 0, 0);
	inline const sf::Color snakeTail(113, 0, 0);
	inline const sf::Color snakeTailEnd(83, 0, 0);

}

