#ifndef TILE_H

#define TILE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Tile:public QObject, public QGraphicsPixmapItem{
	Q_OBJECT
public:
    int type;
    int posX,posY;

	Tile(int type,int posX,int posY);

    void renderTile();

public slots:
	void makeMov();
	void move();

signals:
	void makeMovsignal();
};

#endif
