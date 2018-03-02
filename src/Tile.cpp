#include <QBrush>
#include <QTimer>
#include <QDebug>

#include "Tile.h"
#include "Game.h"

extern Game * game;

Tile::Tile(int type,int posX,int posY){
    //Initializing the parameters for the tile object
	this->type = type;
	this->posX = posX;
	this->posY = posY;

    renderTile();

	connect(this,SIGNAL(makeMovsignal()),this,SLOT(makeMov()));
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

int xToMove = 0, yToMove = 0;
int posXLimit = 0, posYLimit = 0;
int flag = 0;

void Tile::makeMov(){
	qDebug() <<x()<<y()<<"Called";
	qDebug() <<game->brd->player->posX ;
	flag = 0;
	if (game->brd->player->posX == posY && game->brd->player->posY == posX)
	{
		flag = 1;
		game->brd->player->setPos(posY*40,posX*40);
	}
	if (type > 400 && type < 600)
	{
		/* code */
		game->brd->board[posX][posY] = 0;
		if (type%10 != 0)
		{
			// setPos((type%10)*40,0);
			if (type > 500)
			{
				xToMove = (type%10)*40;
				type -= xToMove/20;
			}
			else
			{
				xToMove = ((type - 500)%10)*40;
				type -= xToMove/20;
			}
		}
		else
		{
			if (type > 500)
			{
				yToMove = ((type/10)%10)*40;
				type -= (yToMove/20)*10;
			}
			else
			{
				// xToMove = ((500 - type)%10)*40;
				// type += xToMove/20;
				yToMove = (((type -500)/10)%10)*40;
				type -= (yToMove/20)*10;
			}
			// setPos(0,((type/10)%10)*40);
			// yToMove = ((type/10)%10)*40;
			// type -= (yToMove/20)*10;
		}
		posXLimit += xToMove;
		posYLimit += yToMove;
		posY += xToMove/40;
		posX += yToMove/40;
		qDebug() <<posX << " "<<posY;
		if (flag)
		{
			/* code */
			game->brd->player->posX = posY;
			game->brd->player->posY = posX;
		}
		game->brd->board[posX][posY] = 1;
	}
	QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
	timer->start(50);
}

void Tile::move(){
	// while(xToMove || yToMove){
		if (xToMove != 0)
		{
			if (xToMove > 0 && (posXLimit -  x()) > 0)
			{
				/* code */
				xToMove -= 1;
				setPos(x()+1,y());
				if(flag)
					game->brd->player->setPos(game->brd->player->x()+1,game->brd->player->y());
			}
			else if ((x() - posXLimit) > 0)
			{
				xToMove += 1;
				setPos(x()-1,y());
				if(flag)
					game->brd->player->setPos(game->brd->player->x()-1,game->brd->player->y());
			}
			// posX += 1;
		}
		if (yToMove != 0)
		{
			// yToMove -= 1;
			// setPos(x(),y()+1);
			if (yToMove > 0 && (posYLimit -  y()) > 0)
			{
				/* code */
				yToMove -= 1;
				setPos(x(),y()+1);
				if(flag)
					game->brd->player->setPos(game->brd->player->x(),game->brd->player->y()+1);
			}
			else if ((y() - posYLimit) > 0)
			{
				yToMove += 1;
				setPos(x(),y()-1);
				if(flag)
					game->brd->player->setPos(game->brd->player->x(),game->brd->player->y()-1);
			}
			// posY += 10;
		}
	// }
}
