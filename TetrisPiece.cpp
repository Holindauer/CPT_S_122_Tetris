#include "TetrisPiece.hpp"



TetrisPiece::~TetrisPiece(){

    for (int i=0; i<this->buidlingBlocks.size(); i++){

        // delete if not null ptr
        if (this->buidlingBlocks[i] != nullptr){
            
            // delete and replace with nullptr
            delete this->buidlingBlocks[i];
            this->buidlingBlocks[i] = nullptr;
        }
    }
}