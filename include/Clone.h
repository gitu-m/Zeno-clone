#ifndef CLONE_H

#define CLONE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <chrono>
#include <vector>
#include <mutex>

#include "Event.h"

class Clone: public QObject, public QGraphicsRectItem{
    Q_OBJECT


public:
    int posX, posY;

    int run = 1;

    int fadeTrigger = 0;

    std::mutex cloneMutex;
    std::vector<Event> player_events;
    std::chrono::steady_clock::time_point time_spawned;

    QGraphicsScene * scene;

    Clone(const std::vector<Event> player_events, QGraphicsScene * scene,int X, int Y);

signals:

    void makeMove(int , int );
    void cloneDone();

public:

    void start_moving();

};

#endif
