#include "gameLoop.hpp"

#include <cstdlib>
#include <SFML/Graphics.hpp>

void gameLoop(){


    Board board;

	// TODO after a piece is determined to be in an imminent collision.
	// TODO stop the movement and spawn a new piece
	board.newTetrisPiece();

	// TODO make a piece fall periodically throughout the loop
    board.descendFallingPiece();

	// TODO This needs to be called after the RIGHT key is pressed
    board.moveRight();

	// TODO This needs to be called after the LEFT key is pressed
    board.moveLeft();

	// TODO Test SFML display agianst this prinout
    board.printBoard();


    sf::RenderWindow window(sf::VideoMode(320, 800), "Tetris!");

	sf::RectangleShape border(sf::Vector2f(240, 720));
	border.setOutlineThickness(5);
    border.setPosition(40, 40);
    border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::Blue);


    cout << "Starting Board" << endl;

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
