#include "gameLoop.hpp"

#include <cstdlib>
#include <SFML/Graphics.hpp>

void gameLoop(){


    Board board;
	board.newTetrisPiece();

    sf::RenderWindow window(sf::VideoMode(320, 800), "Tetris!");

	sf::RectangleShape border(sf::Vector2f(240, 720));
	border.setOutlineThickness(5);
    border.setPosition(40, 40);
    border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::Blue);



	while (window.isOpen())
	{

		window.clear();
		window.draw(border);
		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

		// 	// update representation in memory
		// 	board.moveRight();
		// }

		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

		// 	// update representation in memory
		// 	board.moveLeft();

		// }

        // system("clear");
        // board.printBoard();
	}


}
