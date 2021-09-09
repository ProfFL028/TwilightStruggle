//
// Created by Administrator on 2021/9/9.
//

#include "../dataStructure/entity/GameEntry.h"
#include <iostream>
using namespace std;

int main() {
    GameEntry game("game player1", 5);

    cout << game.getScore() << endl;

    return 0;
}
