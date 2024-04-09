#pragma once


#include <vector>

using std::vector;

// colors
enum Color { Red, Blue, Green, Yellow};

// Individual squares of game blocks
typedef struct { int row, col; } BuildingBlock;


class GameBlock{
    /**
     * A GameBlock contains the building blocks of a falling tetris piece. The main data
     * component of the GameBlock is a vector of BuildingBLocks. Building blocks contain 
     * the (row, col) indices for a single square of a game block.
     * 
     * Building blocks are moved down the Board class's 2d matrix in a 
     * 
    */

    public:

        GameBlock();

        // vector of building blocks  
        vector<BuildingBlock*> piece;

        // color
        Color color;

        // whether or not to keep moving the piece downward
        bool isMoving;
            
        // movement functions
        void moveDown();
        bool keepMoving(BuildingBlock** board); 




};