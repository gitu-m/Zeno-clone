#include <QBrush>
#include <QTimer>
#include <QDebug>

#include "Tile.h"
#include "Game.h"

extern Game * game;

Tile::Tile(int state,int posX,int posY){
	this->state = state;
	this->posX = posX;
	this->posY = posY;
	setGraphics();
	connect(this,SIGNAL(makeMovsignal()),this,SLOT(makeMov()));
}

void Tile::setGraphics(){
	QBrush brush;

	if (state == 999)
	{
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(QColor(109,76,65));
	}
	else if (state == 1 || state == 255)
	{
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(QColor(215,204,200));
	}
	else if (state > 400 && state < 600)
	{
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(QColor(62,39,35));
	}
	else if (state > 200 && state < 400)
	{
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(QColor(255,193,7));
	}
	setBrush(brush);
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
	if (state > 400 && state < 600)
	{
		/* code */
		game->brd->board[posX][posY] = 0;
		if (state%10 != 0)
		{
			// setPos((state%10)*40,0);
			if (state > 500)
			{
				xToMove = (state%10)*40;
				state -= xToMove/20;
			}
			else
			{
				xToMove = ((state - 500)%10)*40;
				state -= xToMove/20;
			}
		}
		else
		{
			if (state > 500)
			{
				yToMove = ((state/10)%10)*40;
				state -= (yToMove/20)*10;
			}
			else
			{
				// xToMove = ((500 - state)%10)*40;
				// state += xToMove/20;
				yToMove = (((state -500)/10)%10)*40;
				state -= (yToMove/20)*10;
			}
			// setPos(0,((state/10)%10)*40);
			// yToMove = ((state/10)%10)*40;
			// state -= (yToMove/20)*10;
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
