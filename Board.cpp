#include "Board.hpp"

// A lot of O(n^2) but aint nobody playing tetris on an n dimmensional board

// computes 2d index
int Board::index(int row, int col){
    return col + (ySize * row);
}

// constructor
Board::Board(int _xSize, int _ySize){

    // Allocate mem for rows
    
    // populate rows, cols
    for(int row=0; row<_xSize; row++){
        for(int col=0; col<_ySize; col++){  
            
            // initialize board to nullptrs
            board.push_back(nullptr);
        }
    }   
}

// print board for testing
void Board::printBoard(){

    cout << "printing board" << endl;

    // populate rows, cols
    for(int row=0; row<xSize; row++){
        for(int col=0; col<ySize; col++){  
            

            if ( board[index(row, col)] == nullptr){
                cout << "|_|";
            }
            else{
                cout << "X" << endl;

            }
        }

        cout << "\n";
    }

}

