#ifndef BOARD_H
#define BOARD_H
#include "Player.h"
#include "Clone.h"
#include <QGraphicsScene>

class Board: public QGraphicsScene{
    Q_OBJECT

public:
    int l, b;
    int **board;
    Board(QGraphicsScene *scene);
    void genBoard(QGraphicsScene *scene);
    Player * player;
    Clone * past_self;

public slots:
    void make_clone(QGraphicsScene *scene, const std::vector <Event> player_events);

};

#endif // BOARD_H
