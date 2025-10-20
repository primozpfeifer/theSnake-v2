#pragma once
#include "renderer.hpp"


class Game
{
private:
	  
	sf::RenderWindow m_mainWindow;
	Renderer renderer;
	Snake m_snake;
	sf::Vector2i m_foodPosition = { 0, 0 };

	sf::Clock m_gameTimer;
	sf::Keyboard::Key m_lastPressedKey = sf::Keyboard::Unknown;
 
	enum States
	{
		Start,
		Playing,
		GameOver,
		Pause,
		Quit

	};

	States state = Playing;


public:

	Game();
	~Game();

	void run();


private:

	void restart();
	void spawnFood();

	void checkEvents();
	void update();

};