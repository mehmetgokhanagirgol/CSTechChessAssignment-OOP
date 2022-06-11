#include <iostream>
#include <vector>
#include <string>
#include "classDefinitions.h"

using namespace std;

#define row_size 8
#define column_size 8

Piece *checkPiece(char piece){
    Piece *tempPiece;
    switch (piece){
        case 'p':
            tempPiece = new Pawn();
            break;
        case 'a':
            tempPiece = new Knight();
            break;
        case 'f':
            tempPiece = new Bishop();
            break;
        case 'k':
            tempPiece = new Rook();
            break;
        case 'v':
            tempPiece = new Queen();
            break;
        case 's':
            tempPiece = new King();
            break;
        default :
            tempPiece = new NoPiece();
            break;
    }
    return tempPiece;
}


void takeInput(vector<vector<square>> &board){
    // take the input for board, board consists piece and underthreat bool
    // piece consists side,row and column position
    // used inheritance for individual piece types
    string piece;
    Piece *piece_type;
    for(auto i = 0; i < row_size; ++i){
        for(auto j = 0; j < column_size; ++j){
            cin >> piece;
            piece_type = checkPiece(piece[0]);
            piece_type->setSide(piece[1]);
            piece_type->setRowPosition(i);
            piece_type->setColumnPosition(j);
            board[i].push_back({piece_type, false});
        }
    }
}

void threatBoard(vector<vector<square>> &board){
    // for every piece invoke threat method
    for(auto i = 0; i < row_size; ++i){
        for(auto j = 0; j < column_size; ++j){
            board[i][j].piece->threathen(board);
        }
    }
}

void calculatePoints(vector<vector<square>> &board, pair<double, double> &points){
    // for every square check for piece value and if it is underThreat
    for(auto i = 0; i < row_size; ++i){
        for(auto j = 0; j < column_size; ++j){
            if(board[i][j].piece->getSide() == 'b'){
                if(board[i][j].underThreat)
                    points.first += board[i][j].piece->getValue() / 2;
                else
                    points.first += board[i][j].piece->getValue();
            }
            else if(board[i][j].piece->getSide() == 's'){
                if(board[i][j].underThreat)
                    points.second += board[i][j].piece->getValue() / 2;
                else
                    points.second += board[i][j].piece->getValue();
            }
        }
    }
}


int main(){
    ChessBoard chess_board;
    pair<double, double> points = {0, 0};

    // Take input, do the threats for each piece then calculate the points
    takeInput(chess_board.getBoard());
    threatBoard(chess_board.getBoard());
    calculatePoints(chess_board.getBoard(), points);

    cout << "Siyah:" << points.second << " " << "Beyaz:" << points.first << endl;
    return 0;
}