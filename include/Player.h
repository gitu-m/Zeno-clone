#ifndef PLAYER_H

#define PLAYER_H

#include <QGraphicsRectItem>
#include <chrono>
#include <vector>

#include "Event.h"

class Player: public QObject, public QGraphicsRectItem{

    Q_OBJECT

public:
    /*!
    * X co-ordinate of the player object
    */
    int posX;
    /*!
    * Y co-ordinate of the player object
    */
    int posY;

    /*!
    * Checking if the player has triggered the fading tile or not.
    */
    int fadeTrigger = 0;
    /*!
    * This is used to sync the clone and player threads.
    */
    bool isWaiting = false;

    /*!
    * Stores the infromation of the input captured by the player object.
    */
    std::vector <Event> event_queue;

    /*!
    * Stores the time stamp of when the player spawns.
    */
    std::chrono::steady_clock::time_point time_spawned;

    /*!
    * The constructor for the player class.
    * Parameters:
    * initposX,initposY : Co-ordinates of the board's top left corner.
    * playerStartPosX,playerStartPosY : Co-ordinates of the player relative to the board.
    */
    Player(int initposX,int initposY,int playerStartPosX,int playerStartPosY,QGraphicsScene *scene);

    /*!
    * This method is called when the player object receives a keyboard input key.
    */
    void keyPressEvent(QKeyEvent * event);

signals:
    /*!
    * This signal is emitted when the player successfully completes a level.
    */
    void level_over();
    /*!
    * This signal is emitted to spawn a clone when the player acquires a tesseract.
    * Parameters:
    * QGraphicsScene * : The scene to which the clone is to be added.
    * vector : The events which the clone has to go through.
    */
    void clone(QGraphicsScene *, std::vector <Event>);
    /*!
    * This signal is called when a fading tile has been triggered.
    */
    void fadeTileTriggered();

    void gameOverSignal();
};

#endif
