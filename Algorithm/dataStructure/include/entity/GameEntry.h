//
// Created by Administrator on 2021/9/9.
//

#ifndef ALGORITHM_GAMEENTRY_H
#define ALGORITHM_GAMEENTRY_H

#include <iostream>

using namespace std;

class GameEntry {
public:
    GameEntry(const string &n = "", int s = 0);
    string getName() const;
    int getScore() const;

private:
    string name;
    int score;
};


#endif //ALGORITHM_GAMEENTRY_H
