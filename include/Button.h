#ifndef BUTTON_H

#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    /*!
    * The brush member for the button to set its color and parameters.
    */
    QBrush brush;
    /*!
    * The text to be displayed in the button.
    */
    QGraphicsTextItem* text;

    /*!
    * Constructor for the Button class.
    * Parameters :
    * name : The string to be displayed in the button.
    * parent : No clue why this is used but game crashes without it.
    */
    Button(QString name, QGraphicsItem* parent=NULL);

    /*!
    * The response for the button being clicked.
    */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /*!
    * Upon the pointer entering the button rectangle, this method is called.
    */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    /*!
    * Upon the pointer leaving the button rectangle, this method is called.
    */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    /*!
    * This signal is emitted upon clicking the button.
    */
    void clicked();
};

#endif
