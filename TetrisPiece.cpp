#include "TetrisPiece.hpp"

TetrisPiece::TetrisPiece(){
    isMoving = true;
    blockID = (int) std::time(0); // id is creation time
}


// Tetris Piece Destructor
TetrisPiece::~TetrisPiece(){

    for (int i=0; i<this->buildingBlocks.size(); i++){

        // delete if not null ptr
        if (this->buildingBlocks[i] != nullptr){
            
            // delete and replace with nullptr
            delete this->buildingBlocks[i];
            this->buildingBlocks[i] = nullptr;
        }
    }
}

/**
 * collisionDown() checks if there is a BuidlingBlock* on the board directly below that is noe one of the 
 * pieces within the otherBlocksInPiece vector
*/
bool BuildingBlock::collisionDown(BuildingBlock* board[36][12], vector<BuildingBlock*> blocksInPiece){
    cout << "BuidlingBlock::collisionDown()" << endl;

    // compare each block in the tetris piece to the the block directly beneath this on and accumulate a 
    // count of piece comparisons that yield false. If this count matches the size of the blocksInPiece vector, 
    // we are dealing with a buillding block that is not related to the piece
    int count = 0;
    for (int i=0; i<blocksInPiece.size(); i++){ 
        if ( board[row+1][col] != blocksInPiece[i]){ count++;}
    }

    // if we are dealing with a non-tetrispiece block that is not null, there is a collision below 
    if (board[row+1][col] != nullptr && count ==  blocksInPiece.size()) 
    {return true;} else { return false; }    
}


/**
 * check collision down ensures there will be no collision on the provided game board between building blocks 
 * that are part of the TetrisPiece, and building blocks that are not part of the tetris piece
*/
bool TetrisPiece::collisionDown(BuildingBlock* board[36][12]){
    cout << "TetrisPiece::collisionDown()" << endl;

    // check each block for collision
    for (int i=0; i<4; i++){    

        // extract i'th block
        BuildingBlock* block = buildingBlocks[i];

        // check each of the four blocks for collision using BuidlingBlock's collisionDown() 
        for (int j=0; j<4; j++){
            if (block->collisionDown(board, buildingBlocks)){ return true; }
        }
    }   

    // if no alarm triggered, return false
    return false;
}

/** 
 * The moveDown() function checks for if there is a piece directly below its building blocks (that is not
 * one of its building blocks). If there isnt, each piece in the buildingBlocks vector is shifted down in 
 * the provided board array by 
*/
void TetrisPiece::moveDown(BuildingBlock* board[36][12]){
    cout << "TetrisPiece::moveDown()" << endl;
    
    if (this->collisionDown(board) != true && isMoving) {
        cout << "No Colision" << endl;

        // move all 4 blocks down
        for (int i=0; i<4; i++){

            // access block
            BuildingBlock* block = this->buildingBlocks[i];

            // set previous position on the board to nullptr
            board[block->row][block->col] = nullptr;

            // set one unit down the board to the block ptr
            board[block->row][block->col + 1] = block;

            // update the block's position to reflect new board position
            block->col += 1;
        }        
    }
}