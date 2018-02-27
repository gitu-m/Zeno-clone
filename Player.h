#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <chrono>
#include <ctime>
#include "Event.h"

class Player: public QGraphicsRectItem{
public:

    void keyPressEvent(QKeyEvent * event);
    int posX, posY;
    std::chrono::steady_clock::time_point time_spawned;

    std::vector <key_event> event_queue; // To store all the events the player goes through
};

#endif // MYRECT_H
