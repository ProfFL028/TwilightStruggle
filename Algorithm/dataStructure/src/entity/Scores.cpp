//
// Created by Administrator on 2021/9/9.
//

#include "entity/Scores.h"

Scores::Scores(int maxEnt) {
    maxEntries = maxEnt;
    entries = new GameEntry[maxEntries];
    numEntries = 0;
}

Scores::~Scores() {
    delete[] entries;
}

void Scores::add(const GameEntry &e) {
    int newScore = e.getScore();
    if (this->isFull()) {
        if (newScore <= entries[maxEntries - 1].getScore())
            return;
    } else {
        numEntries++;
    }

    int i = numEntries - 2;
    while (i >= 0 && newScore > entries[i].getScore()) {
        entries[i+1] = entries[i];
        i--;
    }
    entries[i+1] = e;
}

GameEntry Scores::remove(int i) throw(IndexOutOfBounds) {
    if (i < 0 || i >= numEntries)
        throw IndexOutOfBounds();
    GameEntry entry = entries[i];
    for (int j = i; j < numEntries - 1; j++) {
        entries[j] = entries[j+1];
    }
    return entry;
}

bool Scores::isFull() const {
    return numEntries == maxEntries;
}