#include <QKeyEvent>
#include <QtConcurrent>
#include <QDebug>
#include <chrono>
#include <QList>
#include <typeinfo>

#include "Tesseract.h"
#include "Tile.h"
#include "Board.h"
#include "Game.h"
#include "Event.h"
#include "Clone.h"
#include "Player.h"

extern Game * game;

Player::Player(int initposX,int initposY,int playerStartPosX,int playerStartPosY,QGraphicsScene *scene){
    //Setting the dimensions and the position
    this->setRect(initposX + 12, initposY + 12,16,16);
    this->posX = playerStartPosX;
    this->posY = playerStartPosY;
    this->setPos(this->posX*40,this->posY*40);

    //Setting the player object to receive keyboard input
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
    scene->addItem(this);

    time_spawned = std::chrono::steady_clock::now();
}

void Player::keyPressEvent(QKeyEvent *event){
    //Creating a new event to store the information of the current input
    Event *key_pressed =  new Event();

    //Storing the input key
    key_pressed->key = new QKeyEvent(QEvent::KeyPress, event->key(),Qt::NoModifier);

    //Storing the time elapsed
    std::chrono::steady_clock::time_point time_event = std::chrono::steady_clock::now();
    key_pressed->key_time = time_event - time_spawned;

    //Storing it in the event queue of the player
    this->event_queue.push_back(*key_pressed);

    //Logic for moving the player object
    if (event->key() == Qt::Key_Left){
        if (posX-1 >= 0 && game->brd->board[posY][posX-1]){
            posX--;
        }
    }

    else if (event->key() == Qt::Key_Right){
        if (posX+1 < game->brd->l && game->brd->board[posY][posX+1]){
            posX++;
        }
    }

    else if (event->key() == Qt::Key_Up){
        if (posY-1 >= 0 && game->brd->board[posY-1][posX]){
            posY--;
        }
    }

    else if (event->key() == Qt::Key_Down){
        if (posY+1 < game->brd->b && game->brd->board[posY+1][posX]){
            posY++;
        }
    }

    //Setting the appropriate position of the player based on the input
    setPos(posX*40, posY*40);

    //Check is player is colliding with another object
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //Iterating through the list of colliding objects to take an appropriate measure
    for (int i = 0; i < colliding_items.size(); i++){
        //If the colliding object is a tesseract
        if (typeid(*colliding_items[i]) == typeid(Tesseract)){
            //Remove the tesseract upon collision
            scene()->removeItem(colliding_items[i]);

            //Deleting the tesseract object
            delete colliding_items[i];

            //Emitting the signal for clone generation
            emit clone(scene(), event_queue);
        }

        //If the colliding object is a tile
        else if (typeid(*colliding_items[i]) == typeid(Tile)){
            //Checking the type of the tile
            int tileType = qgraphicsitem_cast<Tile *>(colliding_items[i])->type;

            //If the tile is the end tile
            if (tileType == 3){
            //Level over
                emit level_over();
            }

            //If the tile is a trigger
            else if (tileType == 4){
                //Invoking the move tile method on the tile which is triggered by current tile
                game->brd->tilePointers[game->brd->thisLevel->moveStartPosX][game->brd->thisLevel->moveStartPosY]->moveTile();
            }
        }
    }
}
