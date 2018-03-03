#ifndef CLONE_H

#define CLONE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <chrono>
#include <vector>

#include "Event.h"

class Clone: public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    int posX, posY;

    std::vector<Event> player_events;
    std::chrono::steady_clock::time_point time_spawned;

    QGraphicsScene * scene;

    Clone(const std::vector<Event> player_events, QGraphicsScene * scene);

signals:

    void makeMove(int , int );

public slots:

    void start_moving();

};

#endif
