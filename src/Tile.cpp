#include <QBrush>
#include <chrono>
#include <QDebug>
#include <QThread>
#include <typeinfo>
#include <QList>

#include "Player.h"
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
        case 7 : setPixmap(QPixmap("./resources/Tiles/trigger.png")); break;
        case 8 : setPixmap(QPixmap("./resources/Tiles/moving.png")); break;
        case 9 : setPixmap(QPixmap("./resources/Tiles/normal.png")); break;
    }
}

int flag = 0, xToMove,yToMove;

void Tile::resetTile(){
	game->brd->board[posY][posX] = 5;
	game->brd->board[posX + (MovEndX-MovStartX)/40][posY + (MovStartY-MovEndY)/40] = 0;
	setPos(game->brd->initposX+posX*40,game->brd->initposX + posY*40);
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

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for ( int i = 0 ; i < colliding_items.size() ; i++){

        if (typeid(*colliding_items[i]) == typeid(Player)){

            //Emit game over signal
            emit game_over();
            return;
        }
    }

}


void Tile::moveTile(){
	this->isTriggered = !(this->isTriggered);

    qDebug() <<x()<<y()<<"Called";
	flag = 0;
	if (game->brd->player->posX == posX && game->brd->player->posY == posY){
		flag = 1;
		game->brd->player->posX = MovEndX;
		game->brd->player->posY = MovEndY;
	}

	xToMove = (MovEndX-MovStartX)*40;
	yToMove = (MovEndY-MovStartY)*40;

	game->brd->board[posY][posX] = 0;
	game->brd->board[posX + xToMove/40][posY + yToMove/40] = 1;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
	timer->start(10);


}

void Tile::move(){
	if (xToMove != 0){
		if (xToMove > 0){

            xToMove -= 1;
			setPos(x()+1,y());
			if(flag)
				game->brd->player->setPos(game->brd->player->x()+1,game->brd->player->y());
		}
		else{

            xToMove += 1;
			setPos(x()-1,y());
			if(flag)
				game->brd->player->setPos(game->brd->player->x()-1,game->brd->player->y());
		}
	}

    if (yToMove != 0){
		if (yToMove > 0 ){

            yToMove -= 1;
			setPos(x(),y()+1);
			if(flag)
				game->brd->player->setPos(game->brd->player->x(),game->brd->player->y()+1);
		}
		else{

			yToMove += 1;
			setPos(x(),y()-1);
			if(flag)
				game->brd->player->setPos(game->brd->player->x(),game->brd->player->y()-1);
		}
	}

    if ( xToMove == 0 && yToMove == 0) delete timer;

}
