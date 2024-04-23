#include "Board.hpp"



/**
 * contrsutor initializes all BuildinBlock ptrs in the board 
 * vector of vector of BuildingBlock ptrs to the nullptr
*/
Board::Board(){
    
    // populate rows, cols
    for(int row=0; row<rows; row++){
        for (int col=0; col<cols; col++){ 
            board[row][col] = nullptr;
        }
    }   
}


/**
 * newTetrisPiece() creates dynamiclaly allocates a new TetrisPiece struct, p[lacing into it dynamically 
 * allocated BuilidingBlock structs that make up a square piece in the upper right corner.
*/
void Board::newTetrisPiece(){

    // create tetris piece container
    TetrisPiece* piece = new TetrisPiece;

    srand(time(0));
	int variable = rand() % 4 + 1;
	switch (variable)
	{
		case 1:
            newTPiece(piece);
			break;
		case 2:
            newSquarePiece(piece);
			break;
		case 3:
            newSPiece(piece);
			break;
		case 4:
            newLongPiece(piece);
			break;	
	}

    // Place new piece in the board's game block map using block id
    pieceIDMap[piece->blockID] = piece;
    pieceIDsOnBoard.push_back(piece->blockID);

    // set currently moving piece to the new tetris piece blockID
    this->movingPieceBlockId = piece->blockID;
}

// places a new square piece on the board
void Board::newSquarePiece(TetrisPiece* piece){

    // place a 2x2 cube in the upper right corner of the board
    for (int row=0; row<2; row++){
        for(int col=0; col<2; col++){

            piece->pushBuildingBlock(row, col, board);
        }
    }  
}

// places a new square piece on the board
void Board::newSPiece(TetrisPiece* piece){

    int placement_rows[4] = {0, 1, 1, 2};
    int placement_cols[4] = {0, 0, 1, 1};

    for (int i=0; i<4; i++){
        piece->pushBuildingBlock(
            placement_rows[i], 
            placement_cols[i], 
            board
        );         
    }  
}


// places a new square piece on the board
void Board::newLongPiece(TetrisPiece* piece){

    int placement_rows[4] = {0, 1, 2, 3};
    int placement_cols[4] = {0, 0, 0, 0};

    for (int i=0; i<4; i++){
        piece->pushBuildingBlock(
            placement_rows[i], 
            placement_cols[i], 
            board
        );         
    }  
}

// places a new square piece on the board
void Board::newTPiece(TetrisPiece* piece){

    int placement_rows[4] = {0, 1, 1, 1};
    int placement_cols[4] = {1, 0, 1, 2};

    for (int i=0; i<4; i++){
        piece->pushBuildingBlock(
            placement_rows[i], 
            placement_cols[i], 
            board
        );         
    }  
}

// Rotates a piece right if there is no collision
void Board::rotateRight(){
    cout << "Rotating Right" << endl;

    // retrieve the currently moving piece and descend it.
    TetrisPiece* piece = pieceIDMap[movingPieceBlockId];
    piece->rotateRight(board);
}


/**
 * @notice descendFallingPiece() accesses the currently moving piece using the movingPieceID key from the gameBlockMape
*/
void Board::descendFallingPiece(){

    // retrieve the currently moving piece and descend it
    TetrisPiece* piece = pieceIDMap[movingPieceBlockId];
    piece->moveDown(board);
}

// Moves play piece right if there is no collision
void Board::moveRight(){

    // retrieve the currently moving piece and descend it.
    TetrisPiece* piece = pieceIDMap[movingPieceBlockId];
    piece->moveRight(board);
}

// Moves play piece right if there is no collision
void Board::moveLeft(){

    // retrieve the currently moving piece and descend it.
    TetrisPiece* piece = pieceIDMap[movingPieceBlockId];
    piece->moveLeft(board);
}

/**
 * @jeff This function prints the state of the board to the terminal. I am using it for testing
 * the computer representation of what is happening in memory. The grpahics displayed at each iter
 * of the game loop will follow the same logic. There will be an update to the comptuer representaion
 * then it will be displayed.
 * 
*/
void Board::printBoard(){

    // cout << "printing board" << endl;

    // populate rows, cols
    for(int row=0; row<rows; row++){
        for(int col=0; col<cols; col++){  

            if (board[row][col] == nullptr) { cout << "~ ";}else { cout << "X ";}
        }
    
        cout << "\n";
    }
}


/**
 * checkFullRow() checks if the specified row is full of BuildingBLock structs
*/
bool Board::checkFullRow(int row){
    cout << "Checking if row " << row << " Is full" << endl; 
    
    int blockCount = 0;

    // check entire contents of row
    for (int col=0; col<12; col++){
        if (board[row][col] != nullptr){ blockCount++; }
    }

    // if 12 blocks fill the row, it is full
    if (blockCount == 12){
        return true;
    }
    return false;
}

/**
 * clearFullRows() clears all full rows on the board. returns true if the pieces were updated
*/
bool Board::clearFullRows(){
    cout << "Attempting to clear full row" << endl;

    bool piecesUpdated = false;

    vector<int> clearedRows;

    // iterate all rows
    for (int row=0; row<36; row++){

        // clear all BuildingBLocks in full rows
        if (checkFullRow(row)){

            cout << "Row " << row << " is full" << endl;
            clearedRows.push_back(row);

            for (int col=0; col<12; col++){
                board[row][col] = nullptr;
            }
            piecesUpdated = true;
        }
    }

    // shift rows if rows were cleared clearing
    if (piecesUpdated == true) {

        shiftAfterClearing(clearedRows);
    }

    return piecesUpdated;
}


// 
void Board::shiftAfterClearing(vector<int> clearedRows){  

    // 1D temp array of building block ptrs (used as 2D array w/ striding)
    BuildingBlock** tempBoard = new BuildingBlock*[36 * 12];

    // intitiall populate temp board wth nullptr
    for (int row=0; row<rows; row++){  
        for(int col=0; col<cols; col++){
            tempBoard[(row*cols) + col] = nullptr;
        }
    }

    int cleared_rows_encountered = 0;

    // create a copy of the board skipping cleared rows
    for (int row=rows-1; row>=0; row--){ // decrement up from the bottom

        // determine if the current row was cleared
        bool clearedRow = false;    
        for (int i=0; i<clearedRows.size(); i++){
            if (row == clearedRows[i]){
                clearedRow = true;
                break;
            }
        }

        // Only copy if the row was not cleared
        if (clearedRow == false){    
            for(int col=0; col<cols; col++){

                // place in shifted position if not out of bounds
                int shifted_row = row+cleared_rows_encountered;
                if (shifted_row >= 0) {
                    tempBoard[(shifted_row * cols) + col] = board[row][col];
                }
            }
        }else{
            cleared_rows_encountered++;

        }
    }

    // copy temp board into og board
    for (int row=0; row<rows; row++){  
        for(int col=0; col<cols; col++){
            board[row][col] = tempBoard[(row*cols) + col];
        }
    }


    // delete temp mem
    delete[] tempBoard;
}



/**
 * updatePieceMap() finds and remoces a specific building block from 
 * within a TetrisPiece wihtin a the pieceIDMap have been cleared
*/
void Board::updatePieceMap(){
    cout << "Updating Piece Map" << endl;

    // update each piece on the voard
    for (int i=0; i<pieceIDsOnBoard.size(); i++){

        // retireve piece id
        int pieceID = pieceIDsOnBoard[i];
        cout << "Piece ID: " << pieceID << endl;

        // retrieve vector of building blocks from the current piece
        vector<BuildingBlock*> buildingBlocks = pieceIDMap[pieceID]->buildingBlocks;

        // remove empty buildingblocks from the vector 
        for (int b=0; b<buildingBlocks.size(); b++){ 
            
            int row = buildingBlocks[b]->row;
            int col = buildingBlocks[b]->col;

            cout << "Checking (" << row << ", " << col << ")" << endl;

            if (board[row][col] == nullptr){
                cout << "Removing (" << row << ", " << col << ")" << endl; 

                buildingBlocks.erase(buildingBlocks.begin() + b);
            }
        }
    }
}

// removes pieces from the board that do not contain anymore building blocks
void Board::removeEmptyTetrisPieces(){

    // remove any empty pieces after clearing rows
    for (int i=0; i<pieceIDsOnBoard.size(); i++){

        // retireve piece id
        int pieceID = pieceIDsOnBoard[i];

        // retrieve vector of building blocks from the current piece 
        vector<BuildingBlock*> buildingBlocks = pieceIDMap[pieceID]->buildingBlocks;
        
        // If there are no more building blocks, remove the piece
        if (buildingBlocks.size() == 0){

            // remove piece from piece IDs on Board
            pieceIDsOnBoard.erase(pieceIDsOnBoard.begin() + i);
            pieceIDMap.erase(pieceID);
        }
    }
}


// Checks if a position on the board is empty
bool Board::isEmpty(int x, int y){

    if (board[x][y] == nullptr) { return true; }
    else { return false; }
}

void Board::setBlock(int x, int y, BuildingBlock* block)
{
    board[x][y] = block;
}

void Board::newTestPiece(int variable){

    // create tetris piece container
    TetrisPiece* piece = new TetrisPiece;

	switch (variable)
	{
		case 1:
            newTPiece(piece);
			break;
		case 2:
            newSquarePiece(piece);
			break;
		case 3:
            newSPiece(piece);
			break;
		case 4:
            newLongPiece(piece);
			break;	
	}

    // Place new piece in the board's game block map using block id
    pieceIDMap[piece->blockID] = piece;
    pieceIDsOnBoard.push_back(piece->blockID);

    // set currently moving piece to the new tetris piece blockID
    this->movingPieceBlockId = piece->blockID;
}

