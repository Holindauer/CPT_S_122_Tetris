#include <SFML/Graphics.hpp>

class Cell 
{
    public:
    Cell();

	void setPosition(int width, int height);
    sf::Vector2f getPosition();
    void setCellColor(int Color);
    void setCellX(int length); // col
    void setCellY(int height); // row

    sf::RectangleShape cellShape;

    int cellX;
    int cellY;
};