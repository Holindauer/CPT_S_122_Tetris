#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>

#include "TetrisPiece.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

// SFML branch demo

class Board {
    /**
     * The Board class is the computer representation of the game. The board is represented as a static 2D array 
     * of BuildingBLock ptrs. 
     * 
     * a ___ of TetrisPieces is used to contian groups of BuildingBlock ptrs within the 
     * board array that together make up compound pieces. The 
     * 
    */


    public:

        // board setup
        Board();

        // board dims must match board static arr
        int rows=36, cols=12;

        // vector of vectors of building block ptrs representing the
        BuildingBlock* board[36][12];

        // the blockID of the piece that is currently moving
        int movingPieceBlockId; 

        // pieceIDMap maps the blockIdentifier within each BuildingBlock struct to the 
        // GameBLock ptr it belongs to.
        unordered_map<int, TetrisPiece*> pieceIDMap;

        // blockID's of tetris blocks on the board make sure to .erase() tetris pieces 
        // that do not have any remianing BuildingBlocks on the board when displaying
        vector<int> pieceIDsOnBoard;



        // placeds a game block at the top of the board
        void newTetrisPiece();

        // moves the currently moving piece down 1
        void descendFallingPiece();

        // player movement functions
        void moveRight();
        void moveLeft();

        // print board for testing 
        void printBoard();      
};