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

class Level{
public:
    // Level();
    int **levelBoard;

    // BoardDimensions
    int length = 0;
    int breath = 0;
    //Player start position
    int playerStartPosX = 0;
    int playerStartPosY = 0;

    //Movable tile start position
    int moveStartPosX = 0;
    int moveStartPosY = 0;

    //Movable tile end position
    int moveEndPosX = 0;
    int moveEndPosY = 0;

    //Fade tile trigger
    int fadeTriggerPosX = 0;
    int fadeTriggerPosY = 0;

    //Fade tile positions
    int fadeTileCount = 0;
    int **fadeTiles;
};



#endif
