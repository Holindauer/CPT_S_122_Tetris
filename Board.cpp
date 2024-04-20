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
void Board::newTetrisBlock(){

    // create tetris piece container
    TetrisPiece* piece = new TetrisPiece;

    // place a 2x2 cube in the upper right corner of the board -----
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

        // Place new piece in the board's game block map using block id
        pieceIDMap[piece->blockID] = piece;
        pieceIDsOnBoard.push_back(piece->blockID);

        // set currently moving piece to the new tetris piece blockID
        this->movingPieceBlockId = piece->blockID;

    }
}

void Board::newTetrisPole()
{
    // create tetris piece container
    TetrisPiece* piece = new TetrisPiece;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 1; col++) {
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

    // Place new piece in the board's game block map using block id
    pieceIDMap[piece->blockID] = piece;
    pieceIDsOnBoard.push_back(piece->blockID);

    // set currently moving piece to the new tetris piece blockID
    this->movingPieceBlockId = piece->blockID;
    }
}

void Board::newTetrisL()
{
    // create tetris piece container
    TetrisPiece* piece = new TetrisPiece;
    int jBlockPattern[4][2] = {{0,0}, {1,0}, {1,1}, {1,2}};

    for (int i = 0; i < 4; i++) {
            int row = jBlockPattern[i][0];
            int col = jBlockPattern[i][1];

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

    // Place new piece in the board's game block map using block id
    pieceIDMap[piece->blockID] = piece;
    pieceIDsOnBoard.push_back(piece->blockID);

    // set currently moving piece to the new tetris piece blockID
    this->movingPieceBlockId = piece->blockID;
} 

void Board::newTetrisFlat()
{
    // create tetris piece container
    TetrisPiece* piece = new TetrisPiece;
    int jBlockPattern[4][2] = {{0,0}, {0,1}, {0,2}};

    for (int i = 0; i < 4; i++) {
            int row = jBlockPattern[i][0];
            int col = jBlockPattern[i][1];

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


/**
 * checkFullRow() checks if the specified row is full of BuildingBLock structs
*/
bool Board::checkFullRow(int row){
    
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
 * clearFullRows() clears all full rows on the board
*/
void Board::clearFullRows(){

    bool piecesUpdated = false;

    for (int row=0; row<36; row++){

        // clear all BuildingBLocks in full rows
        if (checkFullRow(row)){
            for (int col=0; col<12; col++){
                board[row][col] = nullptr;
            }
            piecesUpdated = true;
        }
    }

    if (piecesUpdated){
        updatePieceMap();
    }
}

/**
 * updatePieceMap() finds and remoces a specific building block from 
 * within a TetrisPiece wihtin a the pieceIDMap have been cleared
*/
void Board::updatePieceMap(){

    for (int i=0; i<pieceIDsOnBoard.size(); i++){

        // retireve piece id
        int pieceID = pieceIDsOnBoard[i];

        // retrieve vector of building blocks from the current piece 
        vector<BuildingBlock*> buildingBlocks = pieceIDMap[pieceID]->buildingBlocks;

        // remove empty buildingblocks from the vector 
        for (int b=0; b<buildingBlocks.size(); i++){ 
            
            int row = buildingBlocks[b]->row;
            int col = buildingBlocks[b]->col;

            if (board[row][col] == nullptr){
                buildingBlocks.erase(buildingBlocks.begin() + b);
            }
        }
    }

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

bool Board::isEmpty(int x, int y)
{
    if (board[x][y] == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}