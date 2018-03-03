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
    //Check if the player is waiting
    while(isWaiting);

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
        if (posX-1 >= 0 && game->brd->board[posY][posX-1] && game->brd->board[posY][posX-1] != 8){
            posX--;
        }
    }

    else if (event->key() == Qt::Key_Right){
        if (posX+1 < game->brd->l && game->brd->board[posY][posX+1] && game->brd->board[posY][posX+1] != 8){
            posX++;
        }
    }

    else if (event->key() == Qt::Key_Up){
        if (posY-1 >= 0 && game->brd->board[posY-1][posX] && game->brd->board[posY-1][posX] != 8){
            posY--;

//            qDebug() << game->brd->board[posY][posX];
        }
    }

    else if (event->key() == Qt::Key_Down){
        if (posY+1 < game->brd->b && game->brd->board[posY+1][posX] && game->brd->board[posY+1][posX] != 8){
            posY++;
        }
    }

    //Setting the appropriate position of the player based on the input
    setPos(posX*40, posY*40);

    qDebug() << game->brd->board[posY][posX];

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

            if(game->brd->tilePointers[game->brd->thisLevel->moveStartPosY][game->brd->thisLevel->moveStartPosX]->isTriggered){
                //Setting the position of the moving tile to default position
                game->brd->tilePointers[game->brd->thisLevel->moveStartPosY][game->brd->thisLevel->moveStartPosX]->moveTile();
            }

            //Emitting the signal for clone generation
            emit clone(scene(), event_queue);

            if (fadeTrigger == 1){// Emit untrigger signal

                fadeTrigger = 0;

                emit game->brd->tilePointers[game->brd->thisLevel->fadeTriggerPosY][game->brd->thisLevel->fadeTriggerPosX]->fadeTileUntrigger();
            }
        }

        //If the colliding object is a tile
        else if (typeid(*colliding_items[i]) == typeid(Tile)){
            //Checking the type of the tile
            int tileType = qgraphicsitem_cast<Tile *>(colliding_items[i])->type;

            //If the tile is the end tile
            if (tileType == 3){

                qDebug() << "done";

                //Level over
                emit level_over();
            }

            //If the tile is a trigger
            else if (tileType == 4){

                if (fadeTrigger == 1){// Emit untrigger signal

                    fadeTrigger = 0;

                    emit game->brd->tilePointers[game->brd->thisLevel->fadeTriggerPosY][game->brd->thisLevel->fadeTriggerPosX]->fadeTileUntrigger();
                }

                //Invoking the move tile method on the tile which is triggered by current tile

//                qDebug() << game->brd->thisLevel->movPosX << " " << game->brd->thisLevel->moveStartPosY;
                if(!game->brd->tilePointers[game->brd->thisLevel->moveStartPosY][game->brd->thisLevel->moveStartPosX]->isTriggered){
                    game->brd->tilePointers[game->brd->thisLevel->moveStartPosY][game->brd->thisLevel->moveStartPosX]->moveTile();
                }
            }

            else if(tileType == 7){

                fadeTrigger = 1;
                emit qgraphicsitem_cast<Tile *>(colliding_items[i])->fadeTileTriggered();
            }

            else if(tileType == 8){

                //Game over, emitting level over for now
                //TODO write a game over signal and functionality

                emit level_over();
            }

            else if (fadeTrigger == 1){// Emit untrigger signal

                fadeTrigger = 0;

                emit game->brd->tilePointers[game->brd->thisLevel->fadeTriggerPosY][game->brd->thisLevel->fadeTriggerPosX]->fadeTileUntrigger();

            }
        }
    }
}
