#include "Clone.h"
#include <queue>
#include "Event.h"
#include "Player.h"
#include <QKeyEvent>
#include "Board.h"
#include "Game.h"
#include <chrono>
#include <QList>

#include <QDebug>

extern Game * game;

Clone::Clone(const std::vector<Event> player_events, QGraphicsScene *scene){

    setRect(120 + 12, 120 + 12,16,16);

    scene->addItem(this);

    posX = 0;
    posY = 1;

    setPos(posX*40, posY*40);

    uint i = 0;
    time_spawned = std::chrono::steady_clock::now();

    while( i < player_events.size()){

        if (std::chrono::steady_clock::now() - time_spawned >= player_events[i].key_time){

//            qDebug() << "Move";

            move(player_events[i]);

            i++;

        }
    }

    connect(this, SIGNAL(time_move(Event)), this, SLOT(move(Event)));

};

void Clone::start_moving(const std::vector<Event> player_events, QGraphicsScene *scene){

    scene->addItem(this);
    uint i = 0;
    time_spawned = std::chrono::steady_clock::now();

    while( i < player_events.size()){

        if (std::chrono::steady_clock::now() - time_spawned >= player_events[i].key_time){

//            qDebug() << "Move";

            emit time_move(player_events[i]);

            i++;

        }
    }

//    delete this;

}


void Clone::move(Event this_move){


    if (this_move.key->key() == Qt::Key_Left){ // Move left

        qDebug() << "left";

        posX--;
    }

    else if (this_move.key->key() == Qt::Key_Right){ // Move right

        qDebug() << "right";

        posX++;

    }

    else if (this_move.key->key() == Qt::Key_Up){ //Move up

        qDebug() << "up";

        posY--;
    }

    else if (this_move.key->key() == Qt::Key_Down){ // Move down

        qDebug() << "down";

       posY++;
    }

    setPos(posX*40, posY*40);

//    delete this; // Delete after all events are done

}
