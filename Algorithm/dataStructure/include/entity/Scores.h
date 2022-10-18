//
// Created by Administrator on 2021/9/9.
//

#ifndef ALGORITHM_SCORES_H
#define ALGORITHM_SCORES_H

#include <iostream>
#include "GameEntry.h"
#include "IndexOutOfBounds.h"

using namespace std;

class Scores {
public:
    Scores(int maxEnt = 10);
    ~Scores();
    void add(const GameEntry& e);
    GameEntry remove(int i);

    bool isFull() const;

private:
    int maxEntries;
    int numEntries;
    GameEntry* entries;
};


#endif //ALGORITHM_SCORES_H
