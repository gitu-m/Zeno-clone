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
    /*!
    * Stores the layout of the current level's board.
    */
    int **levelBoard;

    /*!
    * The length of the board.
    */
    int length = 0;
    /*!
    * The breadth of the board.
    */
    int breath = 0;

    /*!
    * Starting X co-ordinate of the player in the current level.
    */
    int playerStartPosX = 0;
    /*!
    * Starting Y co-ordinate of the player in the current level.
    */
    int playerStartPosY = 0;

    /*!
    * X co-ordinate of the movable tile.
    */
    int moveStartPosX = 0;
    /*!
    * Y co-ordinate of the starting tile.
    */
    int moveStartPosY = 0;

    /*!
    * Ending X co-ordinate of the moving tile.
    */
    int moveEndPosX = 0;
    /*!
    * Ending Y co-ordinate of the moving tile.
    */
    int moveEndPosY = 0;

    /*!
    * X co-ordinate of the trigger for the fading tile.
    */
    int fadeTriggerPosX = 0;
    /*!
    * Y co-ordinate of the trigger for the fading tile.
    */
    int fadeTriggerPosY = 0;

    /*!
    * Number of fading tiles is stored in this attribute.
    */
    int fadeTileCount = 0;
    /*!
    * Stores information about the positions of the fading tiles.
    */
    int **fadeTiles;
};

#endif
