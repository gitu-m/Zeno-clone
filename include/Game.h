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
	/*!
	 * An Integer variables which keeps track of current level.
	 */
	int Level;

	QGraphicsScene *scene;
	Board *brd;

    Game();

	void showText(QString,int,int);
	void displayMenu();

public slots:
	void Start();
	void Rules();
	void Close();

	void displayMenuSlot();

};

#endif
