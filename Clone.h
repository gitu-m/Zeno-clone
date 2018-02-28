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
    std::vector<Event> player_events;
    QGraphicsScene * scene;
    Clone(const std::vector<Event> player_events, QGraphicsScene * scene);

    void start_moving();

signals:
    void time_move(Event);
	void makeMov();

// private :
    // void move(Event this_move);

private slots:
	void changePos();
};

#endif // CLONE_H
