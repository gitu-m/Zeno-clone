#ifndef LEVELS_H

#define LEVELS_H

/*
*   0   - No Tile
*   1   - Regular Tile
*   2   - Start Tile
*   3   - End Tile
*   4   - Trigger Tile
*   5   - Moving Tile
*   6   - Tesseract
*   7   - Fade Tile trigger
*   8   - Fade Tile out of focus
*   9   - Fade Tile in focus
*/

struct Level1{
    //Level Layout
//    int level1Board[5][5] = {{1,0,0,0,0},
//                             {2,7,0,0,3},
//                             {0,1,0,0,8},
//                             {6,4,0,0,8},
//                             {1,2,0,0,1}};

    int level1Board[5][5] = {{1,0,0,0,0},
                             {2,1,0,0,3},
                             {0,1,0,0,8},
                             {6,1,0,0,8},
                             {7,1,1,1,1}};

    //Player start position
    int playerStartPosX = 0;
    int playerStartPosY = 1;

    //Trigger tile position
    int triggerPosX = 1;
    int triggerPosY = 3;

    //Movable tile start position
    int moveStartPosX = 1;
    int moveStartPosY = 4;

    //Movable tile end position
    int moveEndPosX = 3;
    int moveEndPosY = 4;

    //Fade tile trigger
    int fadeTriggerPosX = 0;
    int fadeTriggerPosY = 4;

    //Fade tile positions
    int fadeTileCount = 2;
    int fadeTiles[2][2] = {{4,2},
                           {4,3}};

};

#endif
