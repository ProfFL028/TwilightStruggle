//
// Created by Administrator on 2021/9/9.
//

#include "entity/Board.h"

Board::Board(): currentPlayer(1){}

void Board::clearBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

bool Board::isWin(int mark) {
    int win = 3 * mark; // +3 for X and -3 for O
    return ((board[0][0] + board[0][1] + board[0][2] == win) // row 0
            || (board[1][0] + board[1][1] + board[1][2] == win) // row 1
            || (board[2][0] + board[2][1] + board[2][2] == win) // row 2
            || (board[0][0] + board[1][0] + board[2][0] == win) // column 0
            || (board[0][1] + board[1][1] + board[2][1] == win) // column 1
            || (board[0][2] + board[1][2] + board[2][2] == win) // column 2
            || (board[0][0] + board[1][1] + board[2][2] == win) // diagonal
            || (board[2][0] + board[1][1] + board[0][2] == win)); // diagonal
}

int Board::getWinner() {
    if (isWin(X)) return X;
    if (isWin(O)) return O;
    return EMPTY;
}

void Board::putMark(int i, int j) {
    board[i][j] = currentPlayer;
    currentPlayer *= -1;
}

void Board::print() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            switch (board[i][j]) {
                case X:
                    cout << "X";
                    break;
                case O:
                    cout << "O";
                    break;
                case EMPTY:
                    cout << " ";
                    break;
            }
            if (j < 2)
                cout << " | " ;
        }
        if (i < 2)
            cout << endl << "- + - + -" << endl;
    }
}