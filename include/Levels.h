#ifndef LEVELS_H

#define LEVELS_H

struct Level1{
    //Level Layout
    int level1Board[5][5] = {{1,0,0,0,0},{2,1,0,0,3},{0,1,0,0,1},{6,4,0,0,1},{1,5,0,0,1}};

    //Player start position
    int playerStartPosX = 0;
    int playerStartPosY = 1;

    //Movable tile start position
    int moveStartPosX = 1;
    int moveStartPosY = 4;

    //Movable tile end position
    int moveEndPosX = 3;
    int moveEndPosY = 4;
};

#endif
