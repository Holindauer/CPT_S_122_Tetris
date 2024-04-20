#include "gameLoop.hpp"
#include "Board.hpp"
#include "cell.hpp"

// TODO: Make it less sensitive 

// TODO: change x -> R/G/B

// TODO: When Row Clear We Need To Drop Blocks By 2 Levels to progress game
// TODO: Clear bottom row then above row BUG

// TODO: enable multishape -> Origin block must be on left hand side due to collision checks -> Rotation Possible With this??

// TODO: Title Screen and Score

// TODO: Death Condition

// TODO: MultiPlayer

// TODO: Loop Music

void gameLoop(){

	int rows = 36;
	int cols = 12;

    Board board;
	Cell cells[rows][cols];
	int cellSize = 20; // TODO: sync with class

	board.newTetrisPiece();

	// Window and border param
	int window_width = 320;
	int window_height = 800;
	int border_width = 245;
	int border_height = 725;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Tetris!");

	// Border Shape 
	sf::RectangleShape border(sf::Vector2f(border_width, border_height));
	border.setOutlineThickness(5);
    border.setPosition(40, 40);
    border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::Blue);

	// Music 
	sf::Music music;
	music.setVolume(20.f);

	int variable = rand() % 6 + 1;
	string filename = musicPlayer(variable);

	// Incorporate if !music.getStatus() != sf::Music::Playing 
	music.openFromFile(filename);
	music.play();

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

		// Filling With Cells -> TODO: Only Put In FULL Cells
		// TetrisPiece -> New tetris piece sets ID
		// Board -> Takes ID and return piece pointers 
		// vector piece ID 
		// building vecotr -> row and col
		for (int height = 0; height < rows; height++)
		{
			for (int length = 0; length < cols; length++)
			{
				if (!board.isEmpty(height, length))
				{
				cells[height][length].setPosition(cellSize * length, cellSize * height);
				window.draw(cells[height][length].cellShape);
				}
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
		//board.printBoard();
	}


}

string musicPlayer(int variable)
{
	string filename;

	switch (variable)
	{
		case 1:
			filename = "Songs/Thinking.wav";
			break;
		case 2:
			filename = "Songs/3D array.ogg";
			break;
		case 3:
			filename = "Songs/Cody'sDogs.ogg";
			break;
		case 4:
			filename = "Songs/myocardial inf(ra)ction.ogg";
			break;	
		case 5:
			filename = "Songs/Project_2.ogg";
			break;
		case 6:
			filename = "Songs/lost.wav";
			break;
	}

	return filename;
}