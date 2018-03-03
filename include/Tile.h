#ifndef TILE_H

#define TILE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Tile : public QObject, public QGraphicsPixmapItem{
	Q_OBJECT

public:
	//In general for every tile
    int type;
    int posX,posY;

	//For moving tile
	bool isTriggered = false;

	//Common constructor
	Tile(int type,int posX,int posY);

	//Common method to render the tile
    void renderTile();

	//Method to move tile
	void moveTile();
};

#endif
