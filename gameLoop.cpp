#include "gameLoop.hpp"
#include "Board.hpp"
#include "cell.hpp"

// TODO: if time available segment code for readability purposes
// Wen't with HUNTERS multiple shapes -> leaves an extra block for some reason?
// TODO: change x -> R/G/B
// TODO: MultiPlayer

void gameLoop(){

	int rows = 36;
	int cols = 12;

	// Score based on # of TetrisBlocks that have been placed
	sf::Text scoreTxt;
	sf::Font font;
	int score = 1;

	font.loadFromFile("Assets/Fonts/Font.TTF");
	scoreTxt.setFont(font);

	scoreTxt.setCharacterSize(25);
	scoreTxt.setFillColor(sf::Color::White);
	scoreTxt.setPosition(40, 4);

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
	string filename;
	sf::Music music;
	music.setVolume(20.f);

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
	// sf::Time maxPieceFloatTime = sf::seconds(0.128f);
	sf::Time maxPieceFloatTime = sf::seconds(0.08f);

	// time since the piece has descended
	sf::Time timePieceHasFloated = sf::Time::Zero;

	// gameOver status
	bool gameOver = false;
	while (window.isOpen() && gameOver != true)
	{
		window.clear();
		window.draw(border);

		if (music.getStatus() == sf::SoundSource::Status::Stopped)
		{
			filename = musicPlayer();
			music.openFromFile(filename);
			music.play();
		}

		// Filling With Cells -> TODO: Only Put In FULL Cells
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

		string scoreAsString = std::to_string(score);
		string totalString = "Score: " + scoreAsString;
		scoreTxt.setString(totalString);
		window.draw(scoreTxt);

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

				// if there is a collision after placing the piece, end the game
				TetrisPiece* newPiece = board.pieceIDMap[board.movingPieceBlockId];
				if (newPiece->collisionDown(board.board)){
					cout << "GAME OVER" << endl;
					gameOver = true;
					break;
				}
				
				try {	
					// clear any full rows
					if (board.clearFullRows()){
						
						// update board if changes were made
						board.updatePieceMap();
						board.removeEmptyTetrisPieces();
					}

				} catch(...){
					cout << "Error clearing rows" << endl;
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
	}
}

string musicPlayer()
{
	sf::Music music;
	string filename;
	srand(time(0));
	int variable = rand() % 6 + 1;

	switch (variable)
	{
		case 1:
			filename = "Assets/Songs/Thinking.wav";
			break;
		case 2:
			filename = "Assets/Songs/3D array.ogg";
			break;
		case 3:
			filename = "Assets/Songs/Cody'sDogs.ogg";
			break;
		case 4:
			filename = "Assets/Songs/myocardial inf(ra)ction.ogg";
			break;	
		case 5:
			filename = "Assets/Songs/Project_2.ogg";
			break;
		case 6:
			filename = "Assets/Songs/lost.wav";
			break;
	}

	return filename;
}