#ifndef TILE_H

#define TILE_H

#include <QGraphicsRectItem>
#include <QObject>

class Tile:public QObject, public QGraphicsRectItem{
	Q_OBJECT
public:
	Tile(int state,int posX, int posY);
	int state, posX, posY;

private:
	void setGraphics();

public slots:
	void makeMov();
	void move();

signals:
	void makeMovsignal();
};

#endif 
