#ifndef TILE_H

#define TILE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Tile : public QObject, public QGraphicsPixmapItem{
	Q_OBJECT

public:
	/*!
	* This attribute stores the appropriate type of the tile based on it's functionality.
	*/
    int type;

	/*!
	* The co-ordinates to spawn a tile.
	*/
    int posX,posY;

	/*!
	* This variable checks if the current tile has been triggered.
	*/
	bool isTriggered = false;

	/*!
	* The constructor for the tile class.
	* Parameters are self explanatory.
	*/
	Tile(int type,int posX,int posY);

	/*!
	* Method to render the tile on the screen.
	*/
    void renderTile();

	/*!
	* Method to move the current tile.
	*/
	void moveTile();

	/*!
	* Method which resets the state of the tile.
	*/
	void resetTile();

	/*!
	* Starting co-ordinates of the current tile.
	*/
	int MovStartX = 0;
	int MovStartY = 0;

	/*!
	* Ending co-ordinates of the current tile.
	*/
	int MovEndX = 0;
	int MovEndY = 0;

signals:
	/*!
	* This is set of the trigger for the fading tile.
	*/
    void fadeTileTriggered();
	/*!
	* This is to reset the trigger for the fading tile.
	*/
    void fadeTileUntrigger();

    void game_over();

public slots:

	/*!
	* Method to apply the fading effect on a tile
	*/
    void fadeTile();
	/*!
	* Method to reset a fading tile to it's initial state.
	*/
    void unfadeTile();
	/*!
	* Method to simulate a moving tile .
	*/
    void move();

};

#endif
