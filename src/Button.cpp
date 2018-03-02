#include <QGraphicsTextItem>
#include <QBrush>

#include "Button.h"

Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){
    //Setting the dimensions and co-ordinates of the button
    setRect(0,0,144,54);

    //Setting the appropriate color and style for the brush
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    setBrush(brush);

    //Setting the text object to hold the name of the button
    text = new QGraphicsTextItem(name,this);

    //Setting the position of the text in the button
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    //Allowing the button to respond to mouse hovering
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //Emitting the clicked signal upon being clicked
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    //Changing the color when mouse hovers
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    //Changing the color when mouse leaves
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    setBrush(brush);
}
