#include <SFML/Graphics.hpp>

class Cell 
{
    public:
    Cell();

	void setPosition(int width, int height);
    sf::Vector2f getPosition();

    sf::RectangleShape cellShape;
};