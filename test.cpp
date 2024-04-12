#include "Board.hpp"
#include "TetrisPiece.hpp"


int main(void){

    Board board;

    cout << "Starting Board" << endl;

    board.printBoard();

    cout << "After Placing a Piece on the Board" << endl;

    board.newTetrisPiece();
    board.printBoard();


    return 0;
}