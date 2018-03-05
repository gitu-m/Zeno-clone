#ifndef BOARD_H

#define BOARD_H

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QtCore>
#include <QDebug>
#include <thread>

#include "Tile.h"
#include "Player.h"
#include "Clone.h"
#include "Levels.h"
#include "DigitalClock.h"

class Board: public QObject{
    Q_OBJECT

    /*!
    * This is the thread which runs the clone in the background.
    */
    std::thread cloneThread;

public:
    int l;
    /*!
    * Breadth of the current baord.
    */
    int b;
    /*!
    * Represents the state of the board.
    */
    int **board;
    /*!
    * X Co-ordinate of the board on the game area.
    */
    int initposX;
    /*!
    * Y Co-ordinate of the board on the game area.
    */
    int initposY;
    /*!
    * Stores the value of the current level.
    */
    int curLevel;
    /*!
    * Checking if the current board has a clone spawned or not.
    */
    int cloneSpawned = 0;

    /*!
    * Level object reference for the current board.
    */
    Level *thisLevel;
    /*!
    * Player object reference for current baord.
    */
    Player *player;
    /*!
    * Clone object reference for current board.
    */
    Clone *past_self;
    /*!
    * It stores the references to tiles present on the current board.
    */
    Tile ***tilePointers;
    /*!
    * The current scene in which the board is a part of.
    */
	QGraphicsScene *scene;

    //TO-DO
    DigitalClock *clock;
    
    //TO-DO
    QGraphicsProxyWidget * clockProxyWidget;

    /*!
    * The constructor for the board class.
    * Parameters:
    * scene  :  The scene to which the board is to be added.
    * curLevel : The current level to be displayed.
    */
    Board(QGraphicsScene *scene,int curLevel);
    /*!
    * Destructor for the board class.
    */
    ~Board();

    /*!
    * This method generates the board by rendering the tiles in appropriate positions.
    */
    void genBoard(QGraphicsScene *scene);

signals:
    /*!
    * Signal to start the generation of a clone.
    */
    void startClone();

public slots:
    /*!
    * Slot to which the startClone() signal is connected.
    * This essentially creates a new clone.
    */
    void make_clone(QGraphicsScene *scene, const std::vector <Event> player_events);
    /*!
    * Changes the position of the clone to X and Y where X and Y are the co-ordinates.
    */
    void changeClonePos(int X, int Y);
};

#endif
