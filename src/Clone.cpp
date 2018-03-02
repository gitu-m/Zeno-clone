#include <queue>
#include <QKeyEvent>
#include <chrono>
#include <QList>
#include <QtConcurrent>
#include <QDebug>
#include <typeinfo>

#include "Event.h"
#include "Player.h"
#include "Clone.h"
#include "Board.h"
#include "Game.h"

extern Game * game;

Clone::Clone(const std::vector<Event> player_events, QGraphicsScene *scene){

    setRect(120 + 12, 120 + 12,16,16);
    scene->addItem(this);
    posX = 0;
    posY = 1;
    setPos(posX*40, posY*40);

    this->player_events = player_events;
    this->scene = scene;

    run = 1;

};

void Clone::start_moving(){
    qDebug() <<"Called";
    uint i = 0;
    time_spawned = std::chrono::steady_clock::now();

    while( i < player_events.size() && run){

        if (std::chrono::steady_clock::now() - time_spawned >= player_events[i].key_time){

//            qDebug() << "Move";

            // emit time_move(player_events[i]);
            if (player_events[i].key->key() == Qt::Key_Left){ // Move left

                if (posX-1 >= 0 && game->brd->board[posY][posX-1] == 1){

                    posX--;

                }

                qDebug() << "left";
            }

            else if (player_events[i].key->key() == Qt::Key_Right){ // Move right

                if (posX+1 >= 0 && game->brd->board[posY][posX+1] == 1){

                    posX++;

                }

                qDebug() << "right";
            }

            else if (player_events[i].key->key() == Qt::Key_Up){ //Move up

                if (posY-1 >= 0 && game->brd->board[posY-1][posX] == 1){

                    posY--;

                }

                qDebug() << "up";
            }

            else if (player_events[i].key->key() == Qt::Key_Down){ // Move down

                if (posY+1 >= 0 && game->brd->board[posY+1][posX] == 1){

                    posY++;

                }

                qDebug() << "down";
            }

            emit makeMov(posX*40, posY*40);


            i++;

            // QList<QGraphicsItem *> colliding_items = collidingItems();

            // for (int i = 0, n = colliding_items.size(); i < n ; i++){

            //     if (typeid(*colliding_items[i]) == typeid(Tile)){
            //         int checkVal = qgraphicsitem_cast<Tile *> (colliding_items[i]) -> state;
            //         // qDebug() <<checkVal;
            //         if (checkVal > 200 && checkVal < 400){
            //             // emit moveTile()
            //                 qDebug() <<checkVal*1;
            //             if (checkVal%10 != 0)
            //             {
            //                 qDebug() << posX+checkVal%10<< " " << posY;
            //                 emit game->brd->tilePointers[posY][posX+checkVal%10]->makeMovsignal();
            //             }
            //             else
            //             {
            //                 qDebug()  << posX << " " << posY+(checkVal/10)%10 <<game->brd->tilePointers[posY+(checkVal/10)%10][posX]->state;

            //                 emit game->brd->tilePointers[posY+(checkVal/10)%10][posX]->makeMovsignal();
            //             }
            //         }
            //     }
            // }
        }
    }
   // delete this;
}
