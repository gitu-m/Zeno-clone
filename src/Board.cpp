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
    Level1 *thisLevel = new Level1();

    //Setting the board dimensions
    l = 5;
    b = 5;

    //Setting the board's scene to be the current scene
    this->scene = scene;

    //Setting the appropriate start postion for the top right corner
    //to get the padding appropriately
    int initposX = (11-l)*20;
    int initposY = (11-b)*20;

    //Dynamically allocate board and tilePointers
    board = new int*[l];
    tilePointers = new Tile**[l];

    for (int i = 0 ; i < l ; i++){
        board[i] = new int[b];
        tilePointers[i] = new Tile*[b];
    }

    //Copying the state of the current level into this board
    for (int i = 0 ; i < l ; i++){
        for ( int j = 0 ; j < b ; j++){
            board[i][j] = thisLevel->level1Board[i][j];
        }
    }

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < b; ++j) {
            //Checking if an object exists at the current co-ordinates
            if (board[j][i] != 0) {
                tilePointers[j][i] = new Tile(board[j][i],j,i);
                tilePointers[j][i]->setPos(initposX + i*40,initposY + j*40);
                scene->addItem(tilePointers[j][i]); 

                if (board[j][i] == 6){
                    Tesseract * tess = new Tesseract();
                    tess->setPos(initposX + i*40 + 12 ,initposY + 12 + j*40);
                    scene->addItem(tess);
                }

                board[j][i] = 1;
            }
        }
    }

    player = new Player();

    player->time_spawned = std::chrono::steady_clock::now();

    player->setRect(initposX + 12, initposY + 12,16,16);
    player->posX = thisLevel->playerStartPosX;
    player->posY = thisLevel->playerStartPosY;
    player->setPos(player->posX*40, player->posY*40);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    connect(player, SIGNAL(clone(QGraphicsScene *, std::vector <Event>)), this, SLOT(make_clone(QGraphicsScene *, const std::vector <Event>)));
}

void Board::make_clone(QGraphicsScene * scene, const std::vector<Event> player_events){
    qDebug() << "Clone created";

    past_self = new Clone(player_events, scene);

    //Connecting the start clone signal to start moving slot
    connect(this,SIGNAL(startClone()),past_self, SLOT(start_moving()));

    //Connecting the make move signal to change clone pos slot to move the clone
    connect(past_self, &Clone::makeMov , this, &Board::changeClonePos);

    //The clone thread is the new thread which is responsible for clone's movements
    past_self->moveToThread(&cloneThread);

    //Upon clone creation, the start clone signal is emitted
    emit startClone();

    //Starting the clones movement in the new thread
    cloneThread.start();
}

void Board::changeClonePos(int X, int Y){
    //Setting the clone's position to (X,Y)
    past_self->setPos(X, Y);

    //Checking if there are any items colliding with the clone
    QList<QGraphicsItem *> colliding_items = scene->collidingItems(past_self);

    //Iterating through the list to take an appropriate action
    for (int i = 0 ;i < colliding_items.size();i++){
        if (typeid(*colliding_items[i]) == typeid(Tile)){
            int checkVal = qgraphicsitem_cast<Tile *> (colliding_items[i]) -> type;
            qDebug() <<checkVal;
            if (checkVal > 200 && checkVal < 400){
                // emit moveTile()
                    qDebug() <<checkVal*1;
                if (checkVal%10 != 0)
                {
                    qDebug() << X/40+checkVal%10<< " " << Y/40;
                    emit tilePointers[Y/40][X/40+checkVal%10]->makeMovsignal();
                }
                else
                {

                    // qDebug()  << X/40 << " " << Y/40+(checkVal/10)%10 ;
                    qDebug()  << X/40 << " " << Y/40+(checkVal/10)%10 <<tilePointers[Y/40+(checkVal/10)%10][X/40]->type;

                    emit tilePointers[Y/40+(checkVal/10)%10][X/40]->makeMovsignal();
                }
            }
        }
    }
}
