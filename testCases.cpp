#include "testCases.hpp"
#include "TetrisPiece.hpp"
#include "Board.hpp"

// Testing Piece Initialization and Movement and border Coll.
void Tests::TestOne() 
{
    Board board;
    int board_counter = 0;

    cout << "Starting Board" << endl << endl;
    for (int i = 0; i < board.rows; i++) {
        for (int j = 0; j < board.cols; j++)
        {
            if (board.isEmpty(i, j))
            {
                board_counter++;
            }
        }
    }
    
    if (board_counter == (12*36)) {cout << "Good Board Initialization." << endl;}

    board.newTetrisPiece(); // Initialize A Long Piece @ Origin (0,0)
    if (!board.isEmpty(1, 0)) {cout << "Good Piece Initialization" << endl;}

    for (int k = 0; k < 36; k++) {
        board.descendFallingPiece();
    }
    if (!board.isEmpty(35, 0) || !board.isEmpty(36, 0)) {cout << "Good Downward Movement" << endl;}
    
    for (int k = 0; k < 36; k++) {
        board.moveRight();
    }
    
    if (!board.isEmpty(35, 12) || !board.isEmpty(36, 12)) {cout << "Good Side Movement" << endl;}
}

// Checking Piece Collisions
void Tests::TestTwo()
{
    Board board;
    board.newTestPiece(4);

    // Checking for collision checks by going 40
    for (int k = 0; k < 40; k++) {
        board.descendFallingPiece();
    }

    board.newTestPiece(4);
    for (int k = 0; k < 40; k++) {
        board.descendFallingPiece();
    }

    if (!board.isEmpty(32, 0)) {cout << "Good Movement Collisions" << endl;}
    else { cout << "ERROR" << endl;}
}

void Tests::TestThree()
{
    Board board;
    board.newTestPiece(4);
    
    for (int k = 0; k < 3; k++) {
        board.descendFallingPiece();
        board.moveRight();
    }

    board.rotateRight();
    if (!board.isEmpty(3,6)) {cout << "Good Rotation" << endl;}
    else { cout << "ERROR" << endl;}
}

void Tests::TestFour()
{
    Board board;
    BuildingBlock* block = new BuildingBlock;
    int count = 0;

    for (int i = 0; i < 12; i++) {
        board.setBlock(35, i, block);
    }
    
    if (board.checkFullRow(35)) {cout << "Good Full Row Check" << endl;} 
    else { cout << "ERROR" << endl;}

    board.clearFullRows();


    for (int j = 0; j < 12; j++) {
        if (!board.isEmpty(35, j)) {
            count++;
        }
    }

    if (count == 0)
    {
        cout << "Good Row Clear" << endl;
    }
    else { cout << "ERROR" << endl;}
}

// Checking Rotation Collisions
void Tests::TestFive()
{
    Board board;
    board.newTestPiece(3);

    // Checking for collision checks by going 40
    for (int k = 0; k < 40; k++) {
        board.descendFallingPiece();
    }

    board.newTestPiece(3);
    board.moveRight();
    for (int k = 0; k < 40; k++) {
        board.descendFallingPiece();
    }

    board.rotateRight();
    if (!board.isEmpty(32, 1) && !board.isEmpty(33, 1) && !board.isEmpty(33, 2) && !board.isEmpty(34, 2)) {cout << "Good Rotation Collisions" << endl;}
    else { cout << "ERROR" << endl;}
}