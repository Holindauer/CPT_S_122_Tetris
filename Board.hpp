#pragma once

#include <vector>
#include <iostream>

#include "GameBlock.hpp"

using std::cout;
using std::endl;
using std::vector;

class Board {
    /**
     * The Board class contains a vector of vectors of Building block pointers. This is
     * the computer representation of the tetris board in memory, 
     * 
    */


    public:

        // board setup
        Board();

        // board dims must match board static arr
        int rows=36, cols=12;

        // vector of vectors of building block ptrs representing the
        BuildingBlock* board[36][12];

        // tetris pieces
        vector<GameBlock*> pieces;


        // print board
        void printBoard();      
};