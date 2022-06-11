#include "classDefinitions.h"
#include <vector>
#include <string>

using namespace std;

bool inBounds(int i, int j){
    return i >= 0 && i < 8 && j >= 0 && j < 8;
}

ChessBoard::ChessBoard(){
    for(auto i = 0; i < 8; ++i){
        board.push_back({});
    }
}

vector<vector<square>> &ChessBoard::getBoard(){
    return this->board;
}


void Piece::setSide(char sd){
    this->side = sd;
}

char Piece::getSide(){
    return side;
}

int Piece::getRowPosition(){
    return this->rowPosition;
}

int Piece::getColumnPosition(){
    return this->columnPosition;
}

void Piece::setRowPosition(int rowPos){
    this->rowPosition = rowPos;
}

void Piece::setColumnPosition(int colPos){
    this->columnPosition = colPos;
}


void Knight::threathen(vector<vector<square>> &board){
    int threathenedSquareRow;
    int threathenedSquareColumn;
    for(unsigned long k = 0; k < ktv.size(); ++k){
        threathenedSquareRow = (this->rowPosition)+ktv[k].first;
        threathenedSquareColumn = (this->columnPosition)+ktv[k].second;
        if(inBounds(threathenedSquareRow, threathenedSquareColumn) && (side != board[threathenedSquareRow][threathenedSquareColumn].piece->getSide())){
                board[threathenedSquareRow][threathenedSquareColumn].underThreat = true;
        }
    }
}

void Pawn::threathen(vector<vector<square>> &board){
    int threathenedSquareRow;
    int threathenedSquareColumn;
    if(this->side == 'b'){
        for(unsigned long k = 0; k < ptvw.size(); ++k){
            threathenedSquareRow = (this->rowPosition)+ptvw[k].first;
            threathenedSquareColumn = (this->columnPosition)+ptvw[k].second;
            if(inBounds(threathenedSquareRow, threathenedSquareColumn) && (side != board[threathenedSquareRow][threathenedSquareColumn].piece->getSide())){
                board[threathenedSquareRow][threathenedSquareColumn].underThreat = true;
            }
        }
    }
    else if(this->side == 's'){
        for(unsigned long k = 0; k < ptvb.size(); ++k){
            threathenedSquareRow = (this->rowPosition)+ptvb[k].first;
            threathenedSquareColumn = (this->columnPosition)+ptvw[k].second;
            if(inBounds(threathenedSquareRow, threathenedSquareColumn) && (side != board[threathenedSquareRow][threathenedSquareColumn].piece->getSide())){
                board[threathenedSquareRow][threathenedSquareColumn].underThreat = true;
            }
        }
    }
}

void Queen::checkDirections(vector<vector<square>> &board, unsigned long i){
    // go in the direction given till out of bounds or hitting another piece
    // if we hit check which side, if ally do nothing if enemy threathen it
    int tempPositionRow = this->getRowPosition();
    int tempPositionColumn = this->getColumnPosition();
    while(inBounds(tempPositionRow  += directions[i].first, tempPositionColumn +=directions[i].second)){
            if(board[tempPositionRow][tempPositionColumn].piece->getValue() != 0){
                //hit
                if(board[tempPositionRow][tempPositionColumn].piece->getSide() == side)
                    break;
                else{
                    board[tempPositionRow][tempPositionColumn].underThreat = true;
                    break; 
                }
            }
        }
}

void Queen::threathen(vector<vector<square>> &board){
    for(unsigned long i = 0; i < directions.size(); ++i){
        Queen::checkDirections(board, i);
    }
}