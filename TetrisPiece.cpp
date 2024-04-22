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


// places a new building block within the tetris piece at the specified position
void TetrisPiece::pushBuildingBlock(int row, int col, BuildingBlock* board[36][12]){

    // allocate mem for new block
    BuildingBlock* block = new BuildingBlock;

        // place block ptr in the board arr
        board[row][col] = block;

            // set position in upper right corner
        block->row = row;
        block->col = col;

        // set block id for this building block
        block->blockID = this->blockID;

        // push block to the piece vector 
        this->buildingBlocks.push_back(block);
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
            if (((buildingBlocks[i]->col)+1) == 12){ return true; } // If imminent collision w/ right border then return true
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
            if (((buildingBlocks[i]->col)-1) == -1){ return true; } // If imminent collision w/ left border then return true
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


// -------------------------------------------------------------------------------------------------------------- Rotation Functions

void TetrisPiece::rotateCW(BuildingBlock* board[36][12]){

    // get rotated coords
    vector<int> rotatedCoordinates = getRotatedCoordinates();

    // check that rotated coordinates do not cause a collision
    if (rotationCollision(board, rotatedCoordinates)){
        return;
    }

    // If no collision, adjust the position of the pieces on the board

}

// applies right rotation matrix to tetris piece coords. Returns flattened 2D mat
vector<int> TetrisPiece::getRotatedCoordinates(){

    // Retrieve building blocks for the piece
    vector<BuildingBlock*> blocks = this->buildingBlocks;

    // get size of blocks
    int numBlocks = blocks.size();

    // create 2D mat for coordinates in the blocks arr
    vector<int> rowColMatrix;
    vector<int> rotationOutput;

    // populate rowCOlMatrix w/ the coords of the tetrs piece building blocks
    for (int i=0; i<numBlocks; i++){
        rowColMatrix.push_back(buildingBlocks[i]->col); // push x vals
        rotationOutput.push_back(0);
    }
    for (int i=0; i<numBlocks; i++){
        rowColMatrix.push_back(buildingBlocks[i]->row); // push y vals
        rotationOutput.push_back(0);
    }

    // right rotation matrix
    int rightRotation[2][2] = {
        {0, 1}, 
        {-1, 0}
    };

    // matrix multiplication: (2, 2) x (2, 4) --> (2, 4)
    for (int i=0; i<numBlocks; i++){

        // init rotation output matrix
        rotationOutput[0 + i] = 0;
        rotationOutput[numBlocks + i] = 0; // Note: (row*cols) + col indexing   

        for (int j=0; j<2; j++){ // dot product

            rotationOutput[i] += rightRotation[0][j] * rowColMatrix[numBlocks * j + i];
            rotationOutput[numBlocks + i] += rightRotation[1][j] * rowColMatrix[numBlocks * j + i];
        }
    }

    // returned rotaed coordinates
    return rotationOutput;
}

// determines if the new placement determined by getRotatedCoordinates() will result in a collision with another pieces
bool TetrisPiece::rotationCollision(BuildingBlock* board[36][12], vector<int>& rotatedCoords){

    // Retrieve building blocks for the piece
    vector<BuildingBlock*> blocks = this->buildingBlocks;

    int numBlocks = blocks.size();
    
    // check that for the pieces that are
    for (int i=0; i<numBlocks; i++){    

        // get rotated cols
        int rotatedX = rotatedCoords[i];
        int rotatedY = rotatedCoords[numBlocks+i];// Note: (row*cols) + col indexing   

        // check that piece is in the boundaries of the board
        if (rotatedX > 11 || rotatedX < 0){ return true; }
        if (rotatedY > 35 || rotatedY < 0){ return true; }

        // check that if there is a non nulllptr piece on the board in the rotated position,
        // that if belongs to the original tetris piece, otherwise it is a collision
        if (board[rotatedY][rotatedX] != nullptr){

            // check all blocks against the non nullptr
            for (int block=0; block<numBlocks; block++){
                
                // get the original rows, cols for the current block
                int originalX = blocks[block]->col;
                int originalY = blocks[block]->row;

                // if the rotated coord is overlapping with a non original coord, there is a collsion
                if (board[rotatedY][rotatedX] != board[originalY][originalX]){
                    return true;
                }
            }
        }
    }

    // if no non nullptr, non tetris piece block found to be overlapping, 
    return false;
}


// Adjust the coordinates on the board and tetris piece block vector to match the rotated coordinates
void TetrisPiece::applyRotation(BuildingBlock* board[36][12], vector<int>& rotatedCoords){

    if (isMoving){

        // adjust buildingBlocs vector
        for (int i=0; i<buildingBlocks.size(); i++){

            // first set all previous positions on the board to nullptr
            board[buildingBlocks[i]->row][buildingBlocks[i]->col] = nullptr;

            // get rotated cols
            int rotatedX = rotatedCoords[i];
            int rotatedY = rotatedCoords[buildingBlocks.size()+i];// Note: (row*cols) + col indexing   

            // set the previous positon of the building block to the new position
            buildingBlocks[i]->row = rotatedY;
            buildingBlocks[i]->col = rotatedX;

            // set the new position on the board
            board[buildingBlocks[i]->row][buildingBlocks[i]->col] = buildingBlocks[i];
        }   
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
