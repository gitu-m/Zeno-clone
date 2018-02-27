#include "Tile.h"
#include <QBrush>

Tile::Tile(int state){
	this->state = state;
	setGraphics();
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
	setBrush(brush);
}