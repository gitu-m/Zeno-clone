#ifndef BUTTON_H

#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    QBrush brush;
    QGraphicsTextItem* text;

    Button(QString name, QGraphicsItem* parent=NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();
};

#endif
