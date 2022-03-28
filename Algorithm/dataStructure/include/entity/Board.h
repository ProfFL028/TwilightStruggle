//
// Created by Administrator on 2021/9/9.
//

#ifndef ALGORITHM_BOARD_H
#define ALGORITHM_BOARD_H

#include <iostream>

using namespace std;

class Board {
public:
    static const int X = 1, O=-1, EMPTY = 0;
    static const int BOARD_SIZE = 3;

    Board();

    void clearBoard();
    void putMark(int i, int j);
    bool isWin(int mark);
    int getWinner();
    void print();

private:
    int currentPlayer;
    int board[BOARD_SIZE][BOARD_SIZE];
};


#endif //ALGORITHM_BOARD_H
