#ifndef CLONE_H
#define CLONE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <chrono>
#include <queue>
#include "Event.h"

class Clone: public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:

    std::chrono::steady_clock::time_point time_spawned;

    int posX, posY;

    uint i = 0;

    Clone(const std::vector<Event> player_events, QGraphicsScene * scene);

    void start_moving(const std::vector<Event> player_events, QGraphicsScene * scene);

signals:
    void time_move(Event);

private slots:
    void move(Event this_move);

};

#endif // CLONE_H
