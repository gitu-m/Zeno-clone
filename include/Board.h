#ifndef BOARD_H

#define BOARD_H

#include <QGraphicsScene>
#include <QtCore>

#include "Tile.h"
#include "Player.h"
#include "Clone.h"
#include "Levels.h"

class Board: public QObject{
    Q_OBJECT

    QThread cloneThread;

public:
    int l, b;
    int **board;
    int initposX,initposY;

    Level1 *thisLevel;
    Player *player;
    Clone *past_self;
    Tile ***tilePointers;
	QGraphicsScene *scene;

    Board(QGraphicsScene *scene);

    void genBoard(QGraphicsScene *scene);

signals:
    void startClone();

public slots:
    void make_clone(QGraphicsScene *scene, const std::vector <Event> player_events);
    void changeClonePos(int X, int Y);
};

#endif
