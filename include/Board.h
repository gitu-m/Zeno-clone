#ifndef BOARD_H
#define BOARD_H
#include "Player.h"
#include "Clone.h"
#include "Tile.h"
#include <QGraphicsScene>
#include <QtCore>

class Board: public QObject{
    Q_OBJECT

    QThread cloneThread;

public:
    int l, b;
    int **board;

    Player * player;
    Clone * past_self;
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

#endif // BOARD_H
