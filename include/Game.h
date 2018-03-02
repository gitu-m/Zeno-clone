#ifndef GAME_H

#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QWidget>

#include "Player.h"
#include "Board.h"

class Game : public QGraphicsView{
	Q_OBJECT

    QThread mthread;

public:
	int Level;

	QGraphicsScene *scene;
	Board *brd;

    Game();

	void displayMenu();

public slots:
	void Start();
};

#endif
