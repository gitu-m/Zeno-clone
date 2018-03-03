#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QBrush>
#include <iostream>
#include <chrono>
#include <QDebug>
#include <QtConcurrent>
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
    board = new int*[b];
    tilePointers = new Tile**[b];

    for (int i = 0 ; i < b ; i++){
        board[i] = new int[l];
        tilePointers[i] = new Tile*[l];
    }

    //Copying the state of the current level into this board
    for (int i = 0 ; i < b ; i++){
        for(int j = 0 ;j < l;j++){
            board[i][j] = thisLevel->level1Board[i][j];
            //qDebug() << board[i][j];
        }
    }

    for (int i = 0; i < b; ++i) {
        for (int j = 0; j < l; ++j) {
            //Checking if a tile object exists at the current co-ordinates
            if (board[i][j]) {
                //Creating a tile object and associating it with the appropriate positional pointer
                tilePointers[i][j] = new Tile(board[i][j],i,j);
                tilePointers[i][j]->setPos(initposY + j*40,initposX + i*40);

                //Adding the tile to the current scene
                scene->addItem(tilePointers[i][j]);

                //Spawning a tesseract
                if (board[i][j] == 6){
                    Tesseract * tess = new Tesseract();
                    tess->setPos(initposY + 12 + j*40,initposX + i*40 + 12);
                    scene->addItem(tess);
                }
            }
        }
    }

    //Creating a new player object
    player = new Player(initposX,initposY,thisLevel->playerStartPosX,thisLevel->playerStartPosY,scene);

    //Connecting the clone signal emitted by the player object to the make clone slot
    connect(player, SIGNAL(clone(QGraphicsScene *, std::vector <Event>)), this, SLOT(make_clone(QGraphicsScene *, const std::vector <Event>)));
}

void Board::make_clone(QGraphicsScene * scene, const std::vector<Event> player_events){
    past_self = new Clone(player_events, scene);

    //Connecting the start clone signal to start moving slot
    connect(this,SIGNAL(startClone()),past_self, SLOT(start_moving()));

    //Connecting the make move signal to get the clone moving
    connect(past_self, &Clone::makeMove,this,&Board::changeClonePos);

    //Connecting the clone done signal to quit signal of the thread
    connect(past_self, SIGNAL(cloneDone()), &cloneThread, SLOT(quit()));

    //The clone thread is the new thread which is responsible for clone's movements
    past_self->moveToThread(&cloneThread);

    //Upon clone creation, the start clone signal is emitted
    emit startClone();

    //Starting the clones movement in the new thread
    cloneThread.start();
}

void Board::changeClonePos(int X, int Y){
    //Changing the posiyion of the clone
    past_self->setPos(X, Y);

    //Checking if there are any items colliding with the clone
    QList<QGraphicsItem *> colliding_items = scene->collidingItems(past_self);

    //Iterating through the list to take an appropriate action
    for (int i = 0 ;i < colliding_items.size();i++){
        //If the current object is a tile
        if (typeid(*colliding_items[i]) == typeid(Tile)){
            //Storing the type of tile in the tileType variable
            int tileType = qgraphicsitem_cast<Tile *> (colliding_items[i])->type;

            //If the tile is a trigger
            if (tileType == 4){
                //Triggering the movable tile
                tilePointers[thisLevel->moveStartPosY][thisLevel->moveStartPosX]->moveTile();
            }
        }
    }
}
