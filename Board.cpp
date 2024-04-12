#include "Board.hpp"



/**
 * contrsutor initializes all BuildinBlock ptrs in the board 
 * vector of vector of BuildingBlock ptrs to the nullptr
*/
Board::Board(){
    
    
    // populate rows, cols
    for(int row=0; row<rows; row++){
        for (int col=0; col<cols; col++){ 
            board[row][col] = nullptr;
        }
    }   
}

/**
 * @jeff This function prints the state of the board to the terminal. I am using it for testing
 * the computer representation of what is happening in memory. The grpahics displayed at each iter
 * of the game loop will follow the same logic. There will be an update to the comptuer representaion
 * then it will be displayed.
 * 
*/
void Board::printBoard(){

    // cout << "printing board" << endl;

    // populate rows, cols
    for(int row=0; row<rows; row++){
        for(int col=0; col<cols; col++){  

            if (board[row][col] == nullptr) { cout << "~ ";}else { cout << "X ";}
        }
    
        cout << "\n";
    }
}
