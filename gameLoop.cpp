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

    // Start clock
	sf::Clock clock; 

	// set framerate to 60 fps
    const sf::Time frameRate = sf::seconds(1.f / 30.f); // 60 fps

	// time frame has ben on the board
    sf::Time frameTime = sf::Time::Zero;

	// time a piece will float before descending
	sf::Time maxPieceFloatTime = sf::seconds(0.128f);

	// time since the piece has descended
	sf::Time timePieceHasFloated = sf::Time::Zero;


    cout << "Starting Board" << endl;
	while (window.isOpen())
	{
		window.clear();
		window.draw(border);
		window.display();

		// reset elsapsed time
        sf::Time elapsedTime = clock.restart();

		// increment the time this frame has been 
		// on the screen by the time since the reset
        frameTime += elapsedTime;  
		timePieceHasFloated += elapsedTime;

        while (frameTime > frameRate){

			// if a piece has been placed on the board
			if (board.pieceIDMap[board.movingPieceBlockId]->isMoving == false){

				// make a new piece
				board.newTetrisPiece();

				for (int i=0; i<36; i++){
					board.clearFullRows();
				}
			}

			// reset the time the frame has been on the board
            frameTime -= frameRate;

			// descent the piece if it has flaoted longer than the pieceFloatTime, 
			if (timePieceHasFloated > maxPieceFloatTime){

				// reset flaot time 
				timePieceHasFloated -= maxPieceFloatTime;

				// descend piece within the computer representation of the board
				board.descendFallingPiece();
			}


			sf::Event event;
			while (window.pollEvent(event)){

				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

				// update representation in memory
				board.moveRight();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

				// update representation in memory
				board.moveLeft();
				
			}
		}

		// Remove this once the graphics are implemented 
		system("clear");
		board.printBoard();

	}


}
