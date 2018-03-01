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
public:

    Game();
	QGraphicsScene * scene;	
	Board * brd;
	int Level;
	void DisplayMenu();

public slots:
	void Start();
};


#endif
