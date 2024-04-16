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

// -------------------------------------------------------------------------------------------------------------- Collision Check Functions

/**
 * collisionDown() checks if there is a BuidlingBlock* on the board directly below that is noe one of the 
 * pieces within the otherBlocksInPiece vector
*/
bool BuildingBlock::collisionDown(BuildingBlock* board[36][12], vector<BuildingBlock*> blocksInPiece){

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
 * collisionDown() checks if there is a BuidlingBlock* on the board directly below that is noe one of the 
 * pieces within the otherBlocksInPiece vector
*/
bool BuildingBlock::collisionRight(BuildingBlock* board[36][12], vector<BuildingBlock*> blocksInPiece){

    // compare each block in the tetris piece to the the block directly beneath this on and accumulate a 
    // count of piece comparisons that yield false. If this count matches the size of the blocksInPiece vector, 
    // we are dealing with a buillding block that is not related to the piece
    int count = 0;
    for (int i=0; i<blocksInPiece.size(); i++){ 
        if ( board[row][col+1] != blocksInPiece[i]){ count++;}
    }

    // if we are dealing with a non-tetrispiece block that is not null, there is a collision below 
    if (board[row][col+1] != nullptr && count ==  blocksInPiece.size()) 
    {return true;} else { return false; }    
}


/**
 * check collision down ensures there will be no collision on the provided game board between building blocks 
 * that are part of the TetrisPiece, and building blocks that are not part of the tetris piece
*/
bool TetrisPiece::collisionRight(BuildingBlock* board[36][12]){

    // check each block for collision
    for (int i=0; i<4; i++){    

        // extract i'th block
        BuildingBlock* block = buildingBlocks[i];

        // check each of the four blocks for collision using BuidlingBlock's collisionRight() 
        for (int j=0; j<4; j++){
            if (block->collisionRight(board, buildingBlocks)){ return true; }
        }
    }   

    // if no alarm triggered, return false
    return false;
}

/**
 * collisionDown() checks if there is a BuidlingBlock* on the board directly below that is noe one of the 
 * pieces within the otherBlocksInPiece vector
*/
bool BuildingBlock::collisionLeft(BuildingBlock* board[36][12], vector<BuildingBlock*> blocksInPiece){

    // compare each block in the tetris piece to the the block directly beneath this on and accumulate a 
    // count of piece comparisons that yield false. If this count matches the size of the blocksInPiece vector, 
    // we are dealing with a buillding block that is not related to the piece
    int count = 0;
    for (int i=0; i<blocksInPiece.size(); i++){ 
        if ( board[row][col-1] != blocksInPiece[i]){ count++;}
    }

    // if we are dealing with a non-tetrispiece block that is not null, there is a collision below 
    if (board[row][col-1] != nullptr && count ==  blocksInPiece.size()) 
    {return true;} else { return false; }    
}


/**
 * check collision down ensures there will be no collision on the provided game board between building blocks 
 * that are part of the TetrisPiece, and building blocks that are not part of the tetris piece
*/
bool TetrisPiece::collisionLeft(BuildingBlock* board[36][12]){

    // check each block for collision
    for (int i=0; i<4; i++){    

        // extract i'th block
        BuildingBlock* block = buildingBlocks[i];

        // check each of the four blocks for collision using BuidlingBlock's collisionRight() 
        for (int j=0; j<4; j++){
            if (block->collisionLeft(board, buildingBlocks)){ return true; }
        }
    }   

    // if no alarm triggered, return false
    return false;
}



// -------------------------------------------------------------------------------------------------------------- Movement Functions

/** 
 * The moveDown() function checks for if there is a piece directly below its building blocks (that is not
 * one of its building blocks). If there isnt, each piece in the buildingBlocks vector is shifted down in 
 * the provided board array by 
*/
void TetrisPiece::moveDown(BuildingBlock* board[36][12]){

    // check collision
    if (this->collisionDown(board) != true && isMoving) {

        // first set all previous positions on the board to nullptr
        for (int i=0; i<4; i++){
            board[buildingBlocks[i]->row][buildingBlocks[i]->col] = nullptr;
        }       
         
        // the place all on the board the new position of the 
        for (int i=0; i<4; i++){

            // move block's stored position down 1 row
            buildingBlocks[i]->row += 1;

            // place i'th block's ptr at its new position
            board[buildingBlocks[i]->row][buildingBlocks[i]->col] = buildingBlocks[i];
        }        
    }else{
        isMoving = false;      
    }
}

void TetrisPiece::moveRight(BuildingBlock* board[36][12]){

        // check collision
    if (this->collisionRight(board) != true && isMoving) {

        // first set all previous positions on the board to nullptr
        for (int i=0; i<4; i++){
            board[buildingBlocks[i]->row][buildingBlocks[i]->col] = nullptr;
        }       
         
        // the place all on the board the new position of the 
        for (int i=0; i<4; i++){

            // move block's stored position right 1 col
            buildingBlocks[i]->col += 1;

            // place i'th block's ptr at its new position
            board[buildingBlocks[i]->row][buildingBlocks[i]->col] = buildingBlocks[i];
        }        
    }
}

void TetrisPiece::moveLeft(BuildingBlock* board[36][12]){

    // check collision
    if (this->collisionLeft(board) != true && isMoving) {

        // first set all previous positions on the board to nullptr
        for (int i=0; i<4; i++){
            board[buildingBlocks[i]->row][buildingBlocks[i]->col] = nullptr;
        }       
         
        // the place all on the board the new position of the 
        for (int i=0; i<4; i++){

            // move block's stored position left 1 col
            buildingBlocks[i]->col -= 1;

            // place i'th block's ptr at its new position
            board[buildingBlocks[i]->row][buildingBlocks[i]->col] = buildingBlocks[i];
        }        
    }
}