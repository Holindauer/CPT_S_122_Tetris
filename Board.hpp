#pragma once

#include <vector>
#include <iostream>

#include "GameBlock.hpp"

using std::cout;
using std::endl;
using std::vector;

class Board {
    /**
     * The 
     * 
    */


    public:

        // board setup
        Board(int _xSize, int _ySize);

        // Dynamic 1D array of building blocks (2D simulated)
        vector<BuildingBlock*> board;

        // board dimmensions
        int xSize, ySize;

        int index(int row, int col);

        // print board
        void printBoard();      
};