#ifndef BOARD_H

#define BOARD_H

#include <QGraphicsScene>
#include <QtCore>
#include <QDebug>
#include <thread>

#include "Tile.h"
#include "Player.h"
#include "Clone.h"
#include "Levels.h"

class Board: public QObject{
    Q_OBJECT

    std::thread cloneThread;

public:
    int l, b;
    int **board;
    int initposX,initposY;
    int curLevel;

    Level *thisLevel;
    Player *player;
    Clone *past_self;
    Tile ***tilePointers;
	QGraphicsScene *scene;

    Board(QGraphicsScene *scene,int curLevel);
    ~Board();

    void genBoard(QGraphicsScene *scene);

signals:
    void startClone();

public slots:
    void make_clone(QGraphicsScene *scene, const std::vector <Event> player_events);
    void changeClonePos(int X, int Y);
};

#endif
