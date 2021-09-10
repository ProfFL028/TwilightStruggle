//
// Created by Administrator on 2021/9/9.
//

#include "../dataStructure/entity/GameEntry.h"
#include "../dataStructure/entity/Board.h"
#include <iostream>
using namespace std;

int main() {
    GameEntry game("game player1", 5);

    cout << game.getScore() << endl;

    Board board;
    board.clearBoard();
    board.putMark(0, 0);
    board.putMark(1, 1);
    board.putMark(0, 1);
    board.putMark(0, 2);
    board.putMark(2, 0);
    board.putMark(1, 2);
    board.putMark(2, 2);
    board.putMark(2, 1);
    board.putMark(1, 0);

    board.print();

    return 0;
}
