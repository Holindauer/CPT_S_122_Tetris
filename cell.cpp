#include "cell.hpp"
#include "gameLoop.hpp"

Cell::Cell()
{
    cellShape.setSize(sf::Vector2f(10, 10));
    cellShape.setFillColor(sf::Color::White);
}

void Cell::setPosition(int width, int height)
{
    cellShape.setPosition(width, height);
}

sf::Vector2f Cell::getPosition()
{
    return cellShape.getPosition();
}