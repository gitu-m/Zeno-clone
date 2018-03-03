#ifndef PLAYER_H

#define PLAYER_H

#include <QGraphicsRectItem>
#include <chrono>
#include <vector>

#include "Event.h"

class Player: public QObject, public QGraphicsRectItem{

    Q_OBJECT
public:
    int posX, posY;
    int fadeTrigger = 0;

    std::vector <Event> event_queue; 
    std::chrono::steady_clock::time_point time_spawned;

    Player(int initposX,int initposY,int playerStartPosX,int playerStartPosY,QGraphicsScene *scene);

    void keyPressEvent(QKeyEvent * event);

signals:
    void level_over();
    void clone(QGraphicsScene *, std::vector <Event>);
    void fadeTileTriggered();
};

#endif
