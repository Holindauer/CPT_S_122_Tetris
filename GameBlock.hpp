#pragma once


#include <vector>

using std::vector;

// colors
enum Color { Red, Blue, Green, Yellow};



class BuildingBlock {

    public: 
        int row, col;

        /**
         * virtual checkCollision() funciton checks whether there is a piece directly under
         * this building block. This function nmust return true in order for the moveDown()
         * function to apply a change to the position of the block.
        */
        /*virtual*/ bool checkCollision();
        
        /**
         * virtual moveDown() funciton moves an individual piece down the board 
         * one square after applying the checkCollision() function
        */
        /*virtual*/ void moveDown();


};


class GameBlock : public BuildingBlock {

    public:

        GameBlock();

        // vector of building blocks  
        vector<BuildingBlock*> piece;

        // color
        Color color;

        // whether or not to keep moving the piece downward
        bool isMoving;
            
        /**
         * overloaded check collision function for a GameBlock applies the inherited BuidlingBlock
         * checkCollision() function to each BuidingBlock in the GameBlock function.
        */
        bool checkCollision();

        /**
         * overloaded moveDown() function for a GameBlock applies the inherited BuidlingBlock
         * moveDown() function to each BuidingBlock in the GameBlock function.
        */
        void moveDown();


};