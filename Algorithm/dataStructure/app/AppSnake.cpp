//
//  main.cpp
//  snake
//  A classic SNAKE game written in C++ for macOS using NCURSES
//
//  Created by Izloop on 5/23/19.
//  Copyright © 2019 Peter Levi Hornig. All rights reserved.
//

#include <cstdlib>
#include <ncurses.h>

bool gameOver;
const int width = 20, height = 20;
int x,y, FruitX, FruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

int TailX[100], TailY[100];
int nTail = 0;

void Setup() {

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    FruitX = (rand() % width) + 1;
    FruitY = (rand() % height) + 1;
    score = 0;

}

void Draw() {

    clear();

    for (int i = 0; i < width + 2; i++)
        mvprintw(0, i, "+");

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 | i ==21)
                mvprintw(i, j, "#");
            else if (j == 0 | j == 21)
                mvprintw(i, j, "+");
            else if (i == y && j == x)
                mvprintw(i, j, "0");
            else if (i == FruitY && j == FruitX)
                mvprintw(i, j, "0");
            else
                for (int k = 0; k < nTail; k++)
                {
                    if (TailX[k] == j && TailY[k] == i)
                        mvprintw(i, j, "o");
                }
        }
    }

    mvprintw(23, 0, "Score %d", score);

    refresh();


}

void Input() {

    keypad(stdscr, TRUE);
    halfdelay(1);

    int c = getch();

    switch(c)
    {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case 113:
            gameOver = true;
            break;
    }

}

void Logic() {

    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;

    //THIS MOVES 1ST TAIL PIECE TO THE HEAD - MWAHAHAHA
    TailX[0] = x;
    TailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    if (x > width || x < 1 || y > height){
        gameOver = true;
    }
    if (x == FruitX && y == FruitY)
    {
        score++;
        FruitX = (rand() % width)+1;
        FruitY = (rand() % height)+1;
        nTail++;
    }

    for (int i = 0; i < nTail; i++)
        if (TailX[i] == x && TailY[i] == y)
        {
            gameOver = true;
        }
}

int main() {

    Setup();

    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
    }

    getch();
    endwin();

    return 0;
}