//
// Created by Administrator on 2021/9/9.
//

#include "entity/GameEntry.h"

GameEntry::GameEntry(const string &n, int s) : name(n), score(s) {}

string GameEntry::getName() const {
    return name;
}

int GameEntry::getScore() const {
    return score;
}