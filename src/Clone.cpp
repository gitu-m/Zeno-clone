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

extern Game *game;

Clone::Clone(const std::vector<Event> player_events, QGraphicsScene *scene){
    setRect(120+12,120+12,16,16);
    scene->addItem(this);

    posX = 0;
    posY = 1;

    setPos(posX*40,posY*40);

    this->player_events = player_events;
    this->scene = scene;
};

void Clone::start_moving(){

    qDebug() << "lol";
    run = 1;

    int i=0;


    time_spawned = std::chrono::steady_clock::now();

    while(i < player_events.size() && run){

        if (std::chrono::steady_clock::now() - time_spawned >= player_events[i].key_time){

            if (player_events[i].key->key() == Qt::Key_Left){

                if (posX-1 >= 0 && game->brd->board[posY][posX-1] && game->brd->board[posY][posX-1] != 8){

                    qDebug() << "Left" << '\n';
                    posX--;                
                }
            }

            else if (player_events[i].key->key() == Qt::Key_Right){

                if (posX+1 >= 0 && game->brd->board[posY][posX+1] && game->brd->board[posY][posX+1] != 8){

                    qDebug() << "Right" << '\n';
                    posX++;
                }
            }

            else if (player_events[i].key->key() == Qt::Key_Up){

                if (posY-1 >= 0 && game->brd->board[posY-1][posX] && game->brd->board[posY-1][posX] != 8){

                    qDebug() << "Up" << '\n';
                    posY--;
                }
            }

            else if (player_events[i].key->key() == Qt::Key_Down){

                if (posY+1 >= 0 && game->brd->board[posY+1][posX] && game->brd->board[posY+1][posX] != 8){

                    qDebug() << "Down" << '\n';
                    posY++;
                }
            }

            if (run) emit makeMove(posX*40, posY*40);

            ++i;
        }


    }

    //Make clone invisble
    this->setRect(0,0,0,0);

    emit cloneDone();
}
