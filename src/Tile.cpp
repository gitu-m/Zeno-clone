#include <QBrush>
#include <chrono>
#include <QDebug>
#include <QThread>
#include <typeinfo>

#include "Player.h"
#include "Tile.h"
#include "Game.h"

extern Game *game;

Tile::Tile(int type,int posX,int posY){
    //Initializing the parameters for the tile object
	this->type = type;
	this->posX = posX;
	this->posY = posY;

//    qDebug() << type << " " << posX << " " << posY;

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
        case 7 : setPixmap(QPixmap("./resources/Tiles/trigger.png")); break;
        case 8 : setPixmap(QPixmap("./resources/Tiles/moving.png")); break;
        case 9 : setPixmap(QPixmap("./resources/Tiles/normal.png")); break;
    }
}

void Tile::moveTile(){

	qDebug() << posX <<" " <<posY;
	qDebug() << game->brd->board[posX][posY];

	if(this->isTriggered){
		setPos(x()-80,y());
		game->brd->board[posX][posY] = 5;
	}
	
	else{
		game->brd->board[posX][posY] = 0;
		//Check is player is colliding with another object
		QList<QGraphicsItem *> colliding_items = collidingItems();

		//Iterating through the list of colliding objects to take an appropriate measure
		for (int i = 0; i < colliding_items.size(); i++){
			//If the colliding object is a tesseract
			if (typeid(*colliding_items[i]) == typeid(Player)){
				//Changing the players position
				game->brd->player->isWaiting = true;

				game->brd->player->posX += 2;
				game->brd->player->setPos(game->brd->player->posX*40,game->brd->player->posY*40);

				game->brd->player->isWaiting = false;
			}
		}

		setPos(x()+80,y());
	}

	this->isTriggered = !(this->isTriggered);
}

void Tile::fadeTile(){

     if (this->type == 8){

         this->type = 9;
         game->brd->board[this->posY][this->posX] = 9;
         this->renderTile();
     }

}

void Tile::unfadeTile(){

    if (this->type == 9){

        this->type = 8;
        game->brd->board[this->posY][this->posX] = 8;
        this->renderTile();
    }

}

