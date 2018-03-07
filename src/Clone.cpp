#include <queue>
#include <QKeyEvent>
#include <chrono>
#include <QList>
#include <QtConcurrent>
#include <QDebug>
#include <thread>
#include <typeinfo>

#include "Event.h"
#include "Player.h"
#include "Clone.h"
#include "Board.h"
#include "Game.h"

extern Game *game;

Clone::Clone(const std::vector<Event> player_events, QGraphicsScene *scene,int X,int Y){

    this->setPixmap(QPixmap("./resources/clone.png"));
    this->setOffset(game->brd->initposX+12,game->brd->initposY+12);
    scene->addItem(this);

    posX = X;
    posY = Y;

    setPos(posX*40,posY*40);

    this->player_events = player_events;
    this->scene = scene;

};

void Clone::start_moving(){

    // qDebug() << "lol start";

    uint i=0;


    time_spawned = std::chrono::steady_clock::now();

    while(run && i < player_events.size()){

        if (run && std::chrono::steady_clock::now() - time_spawned >= player_events[i].key_time){

            if (player_events[i].key->key() == Qt::Key_Left){

                if (posX-1 >= 0 && game->brd->board[posY][posX-1] && game->brd->board[posY][posX-1] != 8){

                    // qDebug() << "Left" << '\n';

                    posX--;
                }
            }

            else if (player_events[i].key->key() == Qt::Key_Right){

                if (posX+1 < game->brd->l && game->brd->board[posY][posX+1] && game->brd->board[posY][posX+1] != 8){

                    // qDebug() << "Right" << '\n';

                    posX++;
                }
            }

            else if (player_events[i].key->key() == Qt::Key_Up){

                if (posY-1 >= 0 && game->brd->board[posY-1][posX] && game->brd->board[posY-1][posX] != 8){

                    // qDebug() << "Up" << '\n';

                    posY--;
                }
            }

            else if (player_events[i].key->key() == Qt::Key_Down){

                if (posY+1 < game->brd->b && game->brd->board[posY+1][posX] && game->brd->board[posY+1][posX] != 8){

                    // qDebug() << "Down" << '\n';

                    posY++;
                }
            }

            if (run) emit makeMove(posX*40, posY*40);

            ++i;
        }


    }

    //Make clone invisble
//    if(run) this->setRect(0,0,0,0);

//    emit cloneDone();

    cloneStop = 1;
    // qDebug() << "done !";

}
