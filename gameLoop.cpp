#include "gameLoop.hpp"

#include <cstdlib>
#include <SFML/Graphics.hpp>

void gameLoop(){


    Board board;
	board.newTetrisPiece();

    sf::RenderWindow window(sf::VideoMode(3000, 1000), "Tetris!");

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

			// update representation in memory
			board.moveRight();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

			// update representation in memory
			board.moveLeft();

		}

        // system("clear");
        // board.printBoard();
	}


}