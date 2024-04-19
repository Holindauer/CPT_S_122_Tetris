#include "gameLoop.hpp"
#include "Board.hpp"
#include "cell.hpp"

#include <cstdlib>
#include <SFML/Graphics.hpp>

void gameLoop(){

	int rows = 36;
	int cols = 12;

    Board board;
	Cell cells[rows][cols];
	int cellSize = 30; // TODO: sync with class

	board.newTetrisPiece();

	// TODO Test SFML display agianst this prinout
    board.printBoard();

	// Window and border param
	int window_width = 320;
	int window_height = 800;
	int border_width = 240;
	int border_height = 720;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Tetris!");

	sf::RectangleShape border(sf::Vector2f(border_width, border_height));
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

		// Filling With Cells
		for (int height = 0; height < rows; height++)
		{
			for (int length = 0; length < cols; length++)
			{
				cells[height][length].setPosition(cellSize * length, cellSize * height);
				window.draw(cells[height][length].cellShape);
			}
		}
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
