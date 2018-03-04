#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QBrush>
#include <QList>
#include <iostream>
#include <chrono>
#include <QDebug>
#include <QtConcurrent>
#include <thread>
#include <typeinfo>

#include "Tile.h"
#include "Tesseract.h"
#include "Clone.h"
#include "Board.h"
#include "Player.h"
#include "Levels.h"

/*
*   0   - No Tile
*   1   - Regular Tile
*   2   - Start Tile
*   3   - End Tile
*   4   - Trigger Tile
*   5   - Moving Tile
*   6   - Tesseract
*/

Board::Board(QGraphicsScene * scene){
    //Creating a struct of type Level1
    thisLevel = new Level1();


    //Setting the board dimensions
    l = 5;
    b = 5;

    //Setting the board's scene to be the current scene
    this->scene = scene;

    //Setting the appropriate start postion for the top right corner to get the padding appropriately
    initposX = (11-l)*20;
    initposY = (11-b)*20;

    //Dynamically allocate board and tilePointers
    board = new int*[l];
    tilePointers = new Tile**[l];


    for (int i = 0 ; i < l ; i++){

        board[i] = new int[b];
        tilePointers[i] = new Tile*[b];

        qDebug() << "bug " << i;

    }


    //Copying the state of the current level into this board
    for (int i = 0 ; i < l ; i++){
        for ( int j = 0 ; j < b ; j++){

            board[i][j] = thisLevel->level1Board[i][j];
            //qDebug() << board[i][j];
        }
    }


    for (int i = 0; i < l; ++i) {
           for (int j = 0; j < b; ++j) {


               //Checking if a tile object exists at the current co-ordinates
               if (board[j][i]) {
                   //Creating a tile object and associating it with the appropriate positional pointer
                   tilePointers[j][i] = new Tile(board[j][i],i,j);
                   tilePointers[j][i]->setPos(initposX + i*40,initposY + j*40);

                   //Adding the tile to the current scene
                   scene->addItem(tilePointers[j][i]);

                   //Spawning a tesseract
                   if (board[j][i] == 6){
                       Tesseract * tess = new Tesseract();
                       tess->setPos(initposX + 12 + i*40,initposY + j*40 + 12);
                       scene->addItem(tess);
                   }
               }
           }
       }


    //Connect fade tile trigger signals
    for ( int i = 0 ; i < thisLevel->fadeTileCount ; i++){

        int X = thisLevel->fadeTiles[i][0];
        int Y = thisLevel->fadeTiles[i][1];

        connect(tilePointers[thisLevel->fadeTriggerPosY][thisLevel->fadeTriggerPosX], SIGNAL(fadeTileTriggered()), tilePointers[Y][X], SLOT(fadeTile()));
        connect(tilePointers[thisLevel->fadeTriggerPosY][thisLevel->fadeTriggerPosX], SIGNAL(fadeTileUntrigger()), tilePointers[Y][X], SLOT(unfadeTile()));

    }

//    connect(tilePointers[thisLevel->fadeTriggerPosY][thisLevel->fadeTriggerPosX], SIGNAL(fadeTileTriggered()), tilePointers[3][4], SLOT(fadeTile()));
//    connect(tilePointers[thisLevel->fadeTriggerPosY][thisLevel->fadeTriggerPosX], SIGNAL(fadeTileUntrigger()), tilePointers[3][4], SLOT(unfadeTile()));

    //Creating a new player object
    player = new Player(initposX,initposY,thisLevel->playerStartPosX,thisLevel->playerStartPosY,scene);

    //Connecting the clone signal emitted by the player object to the make clone slot
    connect(player, SIGNAL(clone(QGraphicsScene *, std::vector <Event>)), this, SLOT(make_clone(QGraphicsScene *, const std::vector <Event>)));


}

Board::~Board(){


    past_self->run = 0;
//    cloneThread.~thread();
    cloneThread.detach();
    qDebug() << "lol";
//    delete past_self;
}

void Board::make_clone(QGraphicsScene * scene, const std::vector<Event> player_events){

    past_self = new Clone(player_events, scene);

    past_self->cloneMutex.lock();
    past_self->run = 1;
    past_self->cloneMutex.unlock();

    //Connecting the make move signal to get the clone moving
    connect(past_self, &Clone::makeMove,this,&Board::changeClonePos);

    cloneThread = std::thread(&Clone::start_moving, past_self);


}

void Board::changeClonePos(int X, int Y){
    //Changing the posiyion of the clone
    past_self->setPos(X, Y);

    qDebug() << "lol";

    //Check is player is colliding with another object
    QList<QGraphicsItem *> colliding_items = past_self->collidingItems();

    //Iterating through the list of colliding objects to take an appropriate measure
    for (int i = 0; i < colliding_items.size(); i++){

        //If the colliding object is a tile
        if (typeid(*colliding_items[i]) == typeid(Tile)){

            //Checking the type of the tile
            int tileType = qgraphicsitem_cast<Tile *>(colliding_items[i])->type;

            //If tile had a tesseract
            if(tileType == 6){
                past_self->setRect(0,0,0,0); // Make clone invisible
            }

            //If the tile is a trigger
            if (tileType == 4){

                if (past_self->fadeTrigger == 1){// Emit untrigger signal

                    past_self->fadeTrigger = 0;

                    emit tilePointers[thisLevel->fadeTriggerPosY][thisLevel->fadeTriggerPosX]->fadeTileUntrigger();
                }

                //Invoking the move tile method on the tile which is triggered by current tile
                if(!tilePointers[thisLevel->moveStartPosY][thisLevel->moveStartPosX]->isTriggered){

                    tilePointers[thisLevel->moveStartPosY][thisLevel->moveStartPosX]->moveTile();
                }
            }

            else if(tileType == 7){

                past_self->fadeTrigger = 1;
                emit qgraphicsitem_cast<Tile *>(colliding_items[i])->fadeTileTriggered();
            }

            else if(tileType == 8){

                //Game over, emitting level over for now
                //TODO write a game over signal and functionality

                emit player->level_over();
            }

            else if (past_self->fadeTrigger == 1 && tileType != 7){// Emit untrigger signal

                past_self->fadeTrigger = 0;

                emit tilePointers[thisLevel->fadeTriggerPosY][thisLevel->fadeTriggerPosX]->fadeTileUntrigger();
            }
        }
    }
}
