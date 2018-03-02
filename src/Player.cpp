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

void Player::keyPressEvent(QKeyEvent *event){

    Event key_pressed;

    int flag = 0;

    key_pressed.key = new QKeyEvent(QEvent::KeyPress, event->key(),Qt::NoModifier);

    std::chrono::steady_clock::time_point time_event = std::chrono::steady_clock::now();
    key_pressed.key_time = time_event - time_spawned;




    if (event->key() == Qt::Key_Left){ // Move left
//        std::cout<<"left"<<std::endl;

        if (posX-1 >= 0 && game->brd->board[posY][posX-1] == 1){
            posX--;
            flag = 1;
        }
    }

    else if (event->key() == Qt::Key_Right){ // Move right
//        std::cout<<"right"<<std::endl;

//        qDebug() << " player " << key_pressed.key_time.count();

        if (posX+1 < game->brd->l && game->brd->board[posY][posX+1] == 1){
            posX++;
            flag = 1;
        }
    }

    else if (event->key() == Qt::Key_Up){ //Move up
//        std::cout<<"up"<<std::endl;

        if (posY-1 >= 0 && game->brd->board[posY-1][posX] == 1){
            posY--;
            flag = 1;

        }

    }

    else if (event->key() == Qt::Key_Down){ // Movw down
//        std::cout<<"down"<<std::endl;

        if (posY+1 < game->brd->b && game->brd->board[posY+1][posX] == 1){
            posY++;
            flag = 1;
        }
    }

    if (flag)
    {
        event_queue.push_back(key_pressed); // Push this event to queue
    }

    // delete &key_pressed;
    setPos(posX*40, posY*40);


    //Check is player is colliding with anything

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n ; i++){

        if (typeid(*colliding_items[i]) == typeid(Tesseract)){
            //Remove tesseract
            //TODO add tesseract functionality

            scene()->removeItem(colliding_items[i]);

            delete colliding_items[i];
            emit clone(scene(), event_queue);

        }

        else if (typeid(*colliding_items[i]) == typeid(Tile)){
            int checkVal = qgraphicsitem_cast<Tile *> (colliding_items[i]) -> type;
            // qDebug() <<checkVal;
            if (checkVal == 999){
            //Level over
                if (game->brd->past_self != NULL){
                    game->brd->past_self->run = 0;
                }
                emit level_over();
            }
            else if (checkVal > 200 && checkVal < 400){
                // emit moveTile()
                    qDebug() <<checkVal*1;
                if (checkVal%10 != 0)
                {
                    qDebug() << posX+checkVal%10<< " " << posY;
                    emit game->brd->tilePointers[posY][posX+checkVal%10]->makeMovsignal();
                }
                else
                {
                    qDebug()  << posX << " " << posY+(checkVal/10)%10 <<game->brd->tilePointers[posY+(checkVal/10)%10][posX]->type;

                    emit game->brd->tilePointers[posY+(checkVal/10)%10][posX]->makeMovsignal();
                }
            }
        }
    }
}
