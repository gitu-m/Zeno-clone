#include "Levels.h"

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

/*!
* Stores the information about the levels.
*/
Level LevelData[5];

/*!
* The layout of the zeroth level.
*/
int level0Board[7][7] = {{1,1,1,1,1,1,2},
                         {1,0,0,0,0,0,0},
                         {1,0,1,1,1,1,1},
                         {1,0,1,0,0,0,1},
                         {1,0,1,3,0,0,1},
                         {1,0,0,0,0,0,1},
                         {1,1,1,1,1,1,1}};

/*!
* The layout of the first level.
*/
int level1Board[5][5] = {{3,1,1,1,0},
						 {0,0,0,0,0},
						 {0,0,0,0,2},
						 {0,0,5,0,1},
						 {6,1,1,1,4}};

/*!
* The layout of the second level.
*/
int level2Board[7][7] = {{0,0,0,0,0,0,0},
                         {0,0,0,0,1,1,1},
                         {1,1,1,1,0,1,1},
                         {1,3,1,8,8,8,1},
                         {1,1,1,1,0,2,1},
                         {0,0,0,0,6,1,7},
                         {0,0,0,0,0,0,0}};

/*!
* The layout of the second level.
*/
int level3Board[6][6] = {{1,1,3,0,0,0},
                         {8,0,0,0,0,0},
                         {8,0,0,0,0,0},
                         {1,1,1,7,1,2},
                         {0,0,1,1,0,0},
                         {0,0,0,1,1,6}};

/*!
* The positions of the faded tiles in level 2.
*/
int level2fading[3][2] = {{3,3},{4,3},{5,3}};

/*!
* The positions of the faded tiles in level 3.
*/
int level3fading[2][2] = {{0,1},{0,2}};

/*!
* This method is responisble for generating the level data.
*/
void gen(){

	/*-----------------------------------------------------------------------------------*/
	/*LeveL 0*/
	LevelData[0].length = 7;
	LevelData[0].breath = 7;

	LevelData[0].levelBoard = new int*[LevelData[0].length];
	for (int i = 0 ; i < LevelData[0].length ; i++){
	    LevelData[0].levelBoard[i] = new int[LevelData[0].breath];
	}

	for (int i = 0 ; i < LevelData[0].length ; i++){
	    for ( int j = 0 ; j < LevelData[0].breath ; j++){
	        LevelData[0].levelBoard[i][j] = level0Board[i][j];
	    }
	}

	LevelData[0].playerStartPosX = 6;
	LevelData[0].playerStartPosY = 0;



	/*-----------------------------------------------------------------------------------*/
	/*Level 1*/
	LevelData[1].length = 5;
	LevelData[1].breath = 5;

	LevelData[1].levelBoard = new int*[LevelData[1].length];
	for (int i = 0 ; i < LevelData[1].length ; i++){
	    LevelData[1].levelBoard[i] = new int[LevelData[1].breath];
	}

	for (int i = 0 ; i < LevelData[1].length ; i++){
	    for ( int j = 0 ; j < LevelData[1].breath ; j++){
	        LevelData[1].levelBoard[i][j] = level1Board[i][j];
	    }
	}

	LevelData[1].playerStartPosX = 4;
	LevelData[1].playerStartPosY = 2;

	LevelData[1].moveStartPosX = 2;
    LevelData[1].moveStartPosY = 3;
    LevelData[1].moveEndPosX   = 2;
    LevelData[1].moveEndPosY   = 1;


	/*-----------------------------------------------------------------------------------*/
    /*Level 2*/
    LevelData[2].length = 7;
    LevelData[2].breath = 7;

    LevelData[2].levelBoard = new int*[LevelData[2].length];
    for (int i = 0 ; i < LevelData[2].length ; i++){
        LevelData[2].levelBoard[i] = new int[LevelData[2].breath];
    }

    for (int i = 0 ; i < LevelData[2].length ; i++){
        for ( int j = 0 ; j < LevelData[2].breath ; j++){
            LevelData[2].levelBoard[i][j] = level2Board[i][j];
        }
    }

    LevelData[2].fadeTiles = new int*[2];
    for (int i = 0 ; i < 2 ; i++){
        LevelData[2].fadeTiles[i] = new int[3];
    }

    for (int i = 0 ; i < 2 ; i++){
        for ( int j = 0 ; j < 3 ; j++){
            LevelData[2].fadeTiles[i][j] = level2fading[j][i];
        }
    }

    LevelData[2].moveStartPosX = 2;
    LevelData[2].moveStartPosY = 3;
    LevelData[2].moveEndPosX   = 2;
    LevelData[2].moveEndPosY   = 1;

    LevelData[2].playerStartPosX = 5;
    LevelData[2].playerStartPosY = 4;

    LevelData[2].fadeTriggerPosX = 6;
    LevelData[2].fadeTriggerPosY = 5;
    LevelData[2].fadeTileCount = 3;

    /*-----------------------------------------------------------------------------------*/
    /*Level 3*/

    LevelData[3].length = 6;
    LevelData[3].breath = 6;

    LevelData[3].levelBoard = new int*[LevelData[3].length];
    for (int i = 0 ; i < LevelData[3].length ; i++){
        LevelData[3].levelBoard[i] = new int[LevelData[3].breath];
    }

    for (int i = 0 ; i < LevelData[3].length ; i++){
        for ( int j = 0 ; j < LevelData[3].breath ; j++){
            LevelData[3].levelBoard[i][j] = level3Board[i][j];
        }
    }

    LevelData[3].fadeTiles = new int*[2];
    for (int i = 0 ; i < 2 ; i++){
        LevelData[3].fadeTiles[i] = new int[3];
    }

    for (int i = 0 ; i < 2 ; i++){
        for ( int j = 0 ; j < 3 ; j++){
            LevelData[3].fadeTiles[i][j] = level3fading[j][i];
        }
    }

    LevelData[3].playerStartPosX = 5;
    LevelData[3].playerStartPosY = 3;

    LevelData[3].fadeTriggerPosX = 3;
    LevelData[3].fadeTriggerPosY = 3;
    LevelData[3].fadeTileCount = 2;
}
