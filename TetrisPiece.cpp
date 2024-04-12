#include "TetrisPiece.hpp"


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
 * check collision down ensures there are collision on the provided game board between building blocks 
 * that are part of the TetrisPiece, and building blocks that are not part of the tetris piece
*/
bool TetrisPiece::checkCollisionDown(BuildingBlock* board[36][12]){

    // check each block for collision
    for (int i=0; i<4; i++){    

        // extract i'th block
        BuildingBlock* block = buildingBlocks[i];

        // checl each of the four blocks for collision
        for (int j=0; j<4; j++){

            if ( // below  block is none of the tetris block pieces and isnt nullptr simultaneously
                board[block->row][block->col + 1] != buildingBlocks[0] && 
                board[block->row][block->col + 1] != buildingBlocks[1] && 
                board[block->row][block->col + 1] != buildingBlocks[2] && 
                board[block->row][block->col + 1] != buildingBlocks[3] &&
                board[block->row][block->col + 1] != nullptr
            ) {return false;}
        }
    }   

    // otherwise return true
    return true;
}

/** 
 * The moveDown() function checks for if there is a piece directly below its building blocks (that is not
 * one of its building blocks). If there isnt, each piece in the buildingBlocks vector is shifted down in 
 * the provided board array by 
*/
void TetrisPiece::moveDown(BuildingBlock* board[36][12]){

    
    if (checkCollisionDown(board) != true && isMoving) {




        
    }


}