#include "Board.hpp"
#include "TetrisPiece.hpp"



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

    // place a 2x2 cube in the upper right corner of the board
    for (int row=0; row<2; row++){
        for(int col=0; col<2; col++){

            // allocate mem for new block
            BuildingBlock* block = new BuildingBlock;

            // place block ptr in the board arr
            board[row][col] = block;

            // set position in upper right corner
            block->row = row;
            block->col = col;

            // set block id for this building block
            block->blockID = piece->blockID;

            // push block to the piece vector 
            piece->buildingBlocks.push_back(block);
        }
    }  

    // Place new piece in the board's game block map using block id
    pieceIDMap[piece->blockID] = piece;
    pieceIDsOnBoard.push_back(piece->blockID);

    // set currently moving piece to the new tetris piece blockID
    this->movingPieceBlockId = piece->blockID;
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
