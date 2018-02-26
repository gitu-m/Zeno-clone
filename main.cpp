#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "MyRect.h"
#include "Board.h"

Board * brd;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    // create a scene
    QGraphicsScene * scene= new QGraphicsScene();

    //Creates the Level
    brd = new Board(scene);

    //Create Player
    MyRect * player = new MyRect();

    //Set Player Position
    player->posX = 0;
    player->posY = 0;
    player->setRect(player->posX*40 + 12,player->posY*40 + 12,16,16);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);

    // add a view to visualize the scene
    QGraphicsView * view = new QGraphicsView(scene);

    view->show();
    return a.exec();
}
