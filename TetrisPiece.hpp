#pragma once
#include "TetrisMaster.hpp"


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

        // collisions functions check if there the next building block in the specified 
        // direction that is neither part of the tetris block nor is nullptr 
        virtual bool collisionDown(BuildingBlock* board[36][12], vector<BuildingBlock*> otherBlocksInPiece);
        virtual bool collisionRight(BuildingBlock* board[36][12], vector<BuildingBlock*> otherBlocksInPiece);
        virtual bool collisionLeft(BuildingBlock* board[36][12], vector<BuildingBlock*> otherBlocksInPiece);        
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
        bool collisionRight(BuildingBlock* board[36][12]);
        bool collisionLeft(BuildingBlock* board[36][12]);

        // moves a block down one position if there is now colision
        void moveDown(BuildingBlock* board[36][12]);
        void moveRight(BuildingBlock* board[36][12]);
        void moveLeft(BuildingBlock* board[36][12]);

        // places a new building block within the tetris piece at the specified position
        void pushBuildingBlock(int row, int col, BuildingBlock* board[36][12]);

        int ColorInt; // This is basically a replacement for the enumerated colors

        // rotation functions
        void rotateRight(BuildingBlock* board[36][12]);
        vector<int> getRotatedCoordinates();
        bool rotationCollision(BuildingBlock* board[36][12], vector<int>& rotatedCoords);
        void applyRotation(BuildingBlock* board[36][12], vector<int>& rotatedCoords);

};