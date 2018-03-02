#ifndef PLAYER_H

#define PLAYER_H

#include <QGraphicsRectItem>
#include <chrono>
#include <vector>

#include "Event.h"

class Player: public QObject, public QGraphicsRectItem{

    Q_OBJECT
public:

    void keyPressEvent(QKeyEvent * event);
    int posX, posY;
    std::chrono::steady_clock::time_point time_spawned;

    std::vector <Event> event_queue; // To store all the events the player goes through

signals:
    void level_over();
    void clone(QGraphicsScene *, std::vector <Event>);
};

#endif 
