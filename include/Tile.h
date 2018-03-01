#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>

class Tile: public QGraphicsRectItem{
public:
	Tile(int state);
	int state;

private:
	void setGraphics();	
};

#endif // TILE_H
