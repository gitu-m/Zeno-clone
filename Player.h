#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <chrono>
#include <ctime>

typedef struct node {

    QKeyEvent * key; // The key event that occured
    std::chrono::steady_clock::duration key_time; // Time (since player was created) at which key was pressed

} key_event;

class Player: public QGraphicsRectItem{
public:

    void keyPressEvent(QKeyEvent * event);
    int posX, posY;
    std::chrono::steady_clock::time_point time_spawned;

    std::vector <key_event> event_queue; // To store all the events the player goes through
};

#endif // MYRECT_H
