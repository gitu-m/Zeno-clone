#include <QBrush>
#include <chrono>
#include <QDebug>

#include "Tile.h"
#include "Game.h"

extern Game *game;

Tile::Tile(int type,int posX,int posY){
    //Initializing the parameters for the tile object
	this->type = type;
	this->posX = posX;
	this->posY = posY;

	//Rendering the appropriate image based on the tile's type
    renderTile();
}

void Tile::renderTile(){
    switch(type){
        case 1 : setPixmap(QPixmap("./resources/Tiles/normal.png")); break;
        case 2 : setPixmap(QPixmap("./resources/Tiles/start.png")); break;
        case 3 : setPixmap(QPixmap("./resources/Tiles/end.png")); break;
        case 4 : setPixmap(QPixmap("./resources/Tiles/trigger.png")); break;
        case 5 : setPixmap(QPixmap("./resources/Tiles/moving.png")); break;
        case 6 : setPixmap(QPixmap("./resources/Tiles/normal.png")); break;
    }
}

void Tile::moveTile(){
	while(this->posX != game->brd->thisLevel->moveEndPosX){
		this->posX++;
		this->setPos(x()+40,y());
	}
}
