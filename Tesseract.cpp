#include "Tesseract.h"
#include <QBrush>

Tesseract::Tesseract(){

    this->setRect(0,0,16,16);

    QBrush brush;
    brush.setColor(QColor(00,00,00));
    brush.setStyle(Qt::SolidPattern);

    this->setBrush(brush);

}
