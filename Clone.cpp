#include "Clone.h"
#include <queue>
#include "Event.h"
#include "Player.h"
#include <QKeyEvent>
#include "Board.h"
#include "Game.h"
#include <chrono>
#include <QList>
#include <QtConcurrent>
#include <QDebug>

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
    QFuture<void> future = QtConcurrent::run(this,&Clone::start_moving);
    connect(this,SIGNAL(makeMov()), this, SLOT(changePos()));
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

                qDebug() << "left";

                posX--;
            }

            else if (player_events[i].key->key() == Qt::Key_Right){ // Move right

                qDebug() << "right";

                posX++;

            }

            else if (player_events[i].key->key() == Qt::Key_Up){ //Move up

                qDebug() << "up";

                posY--;
            }

            else if (player_events[i].key->key() == Qt::Key_Down){ // Move down

                qDebug() << "down";

               posY++;
            }

            // setPos(posX*40, posY*40);
            // changePos();
            emit makeMov();

            i++;

        }
    }
    delete this;
}

void Clone::changePos(){
    setPos(posX*40, posY*40);
}
