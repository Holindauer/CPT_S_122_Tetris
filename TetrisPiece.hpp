#pragma once


#include <vector>
#include <ctime>// citation for accessing unix timestamp https://stackoverflow.com/questions/6012663/get-unix-timestamp-with-c
#include <iostream>

using std::cout;
using std::endl;
using std::vector;


// colors
enum Color { Red, Blue, Green, Yellow};



class BuildingBlock {
    /**
     * BuildingBlocks are the elementary units of the TetrisPiece struct. It stores the postion of a single
     * square as well as a unique identifer for the TetrisBlock is belongs to. Movement movement functions 
     * are defined here as well, meaning that individual pieces are moved one at a time, rather than the entire 
     * TetrisPiece.
    */

    public: 

        // postion of the piece on the board
        int row, col;

        // blockID is a unique identifier for BuildingBlocks contained within a TetrisPiece. It is
        // the time of creation for the block in unix time. The 
        int blockID;

        /**
         * checkCollision() function checks whether there is a piece directly under
         * this building block. This function must return true in order for the moveDown()
         * function to apply a change to the position of the block.
        */
        virtual bool collisionDown(BuildingBlock* board[36][12], vector<BuildingBlock*> otherBlocksInPiece);
    
        bool checkCollisionRight();
        bool checkCollisionLeft();
        
        /**
         * moveDown() funciton moves an individual piece down the board 
         * one square after applying the checkCollision() function
        */
        void moveDown();

        void moveRight();
        void moveLeft();
};


class TetrisPiece : public BuildingBlock {
    /**
     * TetrisPiece contains the BuildingBlocks that make up a single tetris piece. This purpose of the class is
     * to enable groups of building blocks to be moved together, while retaining the abilitiy to treat them as 
     * individual units during the clearing of a row.
     * 
     * The TetrisPiece class inherits from the BuildingBLock class in order to coordinate the movement of each 
     * BuildingBlock that makes up the TetrisPiece using the inehrited movement functions.
     * 
     * Note: a TetrisPiece always has four blocks
    */

    public:

        TetrisPiece();
        ~TetrisPiece();

        // vector of building blocks that make up the Tetris piece
        vector<BuildingBlock*> buildingBlocks;

        // color of tetris pice
        Color color;

        // whether or not to keep moving the piece downward
        bool isMoving;

        // unique identifier for this tetris piece in the Board's hash map based on creation time
        int blockID;
            
        /**
         * overloaded check collision function for a GameBlock applies the inherited BuidlingBlock
         * checkCollision() function to each BuidingBlock in the GameBlock function.
        */
        bool collisionDown(BuildingBlock* board[36][12]);

        /**
         * overloaded moveDown() function for a GameBlock applies the inherited BuidlingBlock
         * moveDown() function to each BuidingBlock in the GameBlock function.
        */
        void moveDown(BuildingBlock* board[36][12]);


};