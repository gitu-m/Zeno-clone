#ifndef BOARD_H
#define BOARD_H
#include "Player.h"

#include <QGraphicsScene>

class Board: public QGraphicsScene{

public:
    int l, b;
    int **board;
    Board(QGraphicsScene *scene);
    void genBoard(QGraphicsScene *scene);
    Player * player;

};

#endif // BOARD_H
