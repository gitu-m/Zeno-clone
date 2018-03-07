#ifndef CLONE_H

#define CLONE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <chrono>
#include <vector>
#include <mutex>

#include "Event.h"

class Clone: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    /*!
    * The X co-ordinate of the player in the board.
    */
    int posX;
    /*!
    * The Y co-ordinate of the player in the board.
    */
    int posY;

    /*!
    * This attribute is set to 0 if the clone is supposed to be destroyed at some point during execution.
    */
    int run = 1;

    /*!
    * Checking whether the clone stepped on a fading tile or not.
    */
    int fadeTrigger = 0;
    /*!
    * The Y co-ordinate of the player in the board.
    */
    int cloneStop = 0;

    /*!
    * This mutex is to ensure that there are no sync issues when running concurrently.
    */
    std::mutex cloneMutex;
    /*!
    * This attribute stores the keystrokes and the time at which it occurred in a vector.
    */
    std::vector<Event> player_events;
    /*!
    * This attribute stores the time stamp of when the clone was spawned.
    */
    std::chrono::steady_clock::time_point time_spawned;

    /*!
    * The scene to which the clone belongs to.
    */
    QGraphicsScene * scene;

    /*!
    * The constructor for the clone class.
    * Parameters:
    * player_events : This vector has a copy of all the events the player has gone through till this point of time.
    * scene : The scene to which the clone has to be added.
    * X,Y : Co-ordinates to spawn the clone at.
    */
    Clone(const std::vector<Event> player_events, QGraphicsScene * scene,int X, int Y);

signals:
    /*!
    * This signal emitted to move the clone.
    */
    void makeMove(int , int );
    /*!
    * Signal emitted to indicate that the clone has finished it's execution successfully.
    */
    void cloneDone();

public:
    /*!
    * Slot connected to the appropriate signal to get the clone to start moving.
    */
    void start_moving();


};

#endif
