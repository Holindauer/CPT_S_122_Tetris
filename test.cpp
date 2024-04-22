#include "Board.hpp"
#include "TetrisPiece.hpp"


int main(void){

    Board board;

/*     cout << "Starting Board" << endl;

    board.printBoard();

    cout << "After Placing a Piece on the Board" << endl;

    board.newTetrisPiece();
    board.printBoard();

    cout << "After Moving Down" << endl;
    board.descendFallingPiece();
    board.printBoard();

    cout << "After Moving Right" << endl;
    board.moveRight();
    board.printBoard();

    cout << "After Moving Left" << endl;
    board.moveLeft();
    board.printBoard(); */

    board.newTetrisPiece();

    for (int i = 0; i < 1; i++)
    {
        board.moveRight();
        board.descendFallingPiece();
    }

    board.printBoard();
    cout << endl << endl;
    board.rotatePiece();
    board.printBoard();



    return 0;
}