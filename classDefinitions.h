#include <vector>
#include <string>
#include <typeinfo>

using namespace std;
class Piece;

struct square{
    Piece *piece;
    bool underThreat;
};

class ChessBoard{
    public:
        ChessBoard();
        vector<vector<square>> &getBoard();
    private:
        vector<vector<square>> board;
};

class Piece{
    public:
        virtual double getValue() = 0;
        virtual void threathen(vector<vector<square>> &board) = 0;
        int getRowPosition();
        int getColumnPosition();
        void setRowPosition(int rowPos);
        void setColumnPosition(int colPos);
        char getSide();
        void setSide(char sd);
    protected:
        double value;
        char side;
        int rowPosition;
        int columnPosition;
};

class Pawn: public Piece{
    public:
        double getValue(){
            return 1;
        };
        void threathen(vector<vector<square>> &board);
    private:
        vector<pair<int, int>> ptvb = {{1, 1}, {1, -1}}; // ptvb is acronym for pawnthreatvectorblack
        vector<pair<int, int>> ptvw = {{-1, 1}, {-1, -1}}; // ptvw is acronym for pawnthreatvectorwhite
};

class Knight: public Piece{
    public:
        double getValue(){
            return 3;
        };
        void threathen(vector<vector<square>> &board);
    private:
        vector<pair<int, int>> ktv = {{2, 1},{2, -1},{-2, 1},{-2, -1},{1, 2},{1, -2},{-1, -2},{-1, 2}}; // ktv is acronym for knightthreatvector
};

class Bishop: public Piece{
    public:
        double getValue(){
            return 3;
        };
        void threathen(vector<vector<square>> &){};
};

class Rook: public Piece{
    public:
        double getValue(){
            return 5;
        };
        void threathen(vector<vector<square>> &){};
};

class Queen: public Piece{
    public:
        double getValue(){
            return 9;
        };
        void threathen(vector<vector<square>> &board);
        void checkDirections(vector<vector<square>> &board, unsigned long i);
    private:
        vector<pair<int, int>> directions = {{-1,0},{1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
};

class King: public Piece{
    public:
        double getValue(){
            return 100;
        };
        void threathen(vector<vector<square>> &){};
};

class NoPiece: public Piece{
    public:
        double getValue(){
            return 0;
        };
        void threathen(vector<vector<square>> &){};
};


