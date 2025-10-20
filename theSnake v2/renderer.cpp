#pragma once
#include "renderer.hpp"
#include "config.hpp"


Renderer::Renderer()
{
    m_rendererCell.setSize(sf::Vector2f(config::cellSize, config::cellSize));
    m_rendererCell.setOutlineColor(colors::outline);
    m_rendererCell.setOutlineThickness(-config::cellOutlineThickness);
}

Renderer::~Renderer() {}


void Renderer::render(sf::RenderWindow& mainWindow, Snake& snakeObjHandler, sf::Vector2i foodPosition)
{
    mainWindow.clear();
    drawBackground(mainWindow);
    drawFood(mainWindow, foodPosition);
    drawSnake(mainWindow, snakeObjHandler);
    mainWindow.display();
}

void Renderer::drawBackground(sf::RenderWindow& mainWindow)
{
    for (unsigned int y = 0; y < config::rows; y++)
    {
        for (unsigned int x = 0; x < config::cols; x++)
        {
            m_rendererCell.setPosition(config::cellSize * x, config::cellSize * y);

            if (x == 0 || x == config::cols - 1 || y == 0 || y == config::rows - 1)
                m_rendererCell.setFillColor(colors::border);

            else
                m_rendererCell.setFillColor(colors::empty);

            mainWindow.draw(m_rendererCell);
        }
    }
}

void Renderer::drawFood(sf::RenderWindow& mainWindow, sf::Vector2i foodPosition)
{
    if (foodPosition != sf::Vector2i(0, 0))
    {
        m_rendererCell.setPosition(config::cellSize * foodPosition.x, config::cellSize * foodPosition.y);
        m_rendererCell.setFillColor(colors::food);
        mainWindow.draw(m_rendererCell);
    }
}

void Renderer::drawSnake(sf::RenderWindow& mainWindow, Snake& snakeObjHandler)
{
    for (unsigned int i = 0; i < snakeObjHandler.getCoordinates().size(); i++)
    {
        m_rendererCell.setPosition(config::cellSize * snakeObjHandler.getCoordinates()[i].x, config::cellSize * snakeObjHandler.getCoordinates()[i].y);

        if (i == 0)
            m_rendererCell.setFillColor(colors::snakeHead);

        else if (i == snakeObjHandler.getCoordinates().size() - 1)
            m_rendererCell.setFillColor(colors::snakeTailEnd);

        else
            m_rendererCell.setFillColor(colors::snakeTail);

        mainWindow.draw(m_rendererCell);
    }
}     