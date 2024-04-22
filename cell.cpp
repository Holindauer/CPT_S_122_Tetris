#include "cell.hpp"
#include "gameLoop.hpp"

Cell::Cell()
{
    cellShape.setSize(sf::Vector2f(15, 15));
    cellShape.setFillColor(sf::Color::White);
}

void Cell::setPosition(int width, int height)
{
    cellShape.setPosition(width + 45, height + 45); // +40 to fit within border, +5 to center squares (legnth = 10 and origin = topleft not center)
}

sf::Vector2f Cell::getPosition()
{
    return cellShape.getPosition();
}

void Cell::setCellX(int length)
{
    cellX = length;
}

void Cell::setCellY(int height)
{
    cellY = height;
}

void Cell::setCellColor(int Color)
{
    switch (Color)
    {
        case 1:
            cellShape.setFillColor(sf::Color(90, 30, 190)); 
            break;
        case 2:
            cellShape.setFillColor(sf::Color(25, 160, 170)); 
            break;
        case 3:
            cellShape.setFillColor(sf::Color(160, 150, 25)); 
            break;
        case 4:
            cellShape.setFillColor(sf::Color(10, 115, 50)); 
            break;
    }
}