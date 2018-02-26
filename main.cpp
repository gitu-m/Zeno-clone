#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "MyRect.h"

int l = 5, b = 5;
// int **board;
int board[][5] =  {{1,0,0,0,0},
                    {1,1,0,0,1},
                    {0,1,0,0,1},
                    {0,1,1,1,1},
                    {1,1,0,0,1}};

void genBoard(QGraphicsScene * scene) {
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < b; ++j) {
            if (board[j][i] == 1) {
                QGraphicsRectItem * rect = new QGraphicsRectItem();
                rect->setRect(i*40,j*40,40,40);
                scene->addItem(rect);
            }
        }
    }
}

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    // create a scene
    QGraphicsScene * scene= new QGraphicsScene();

    genBoard(scene);
    

    MyRect * player = new MyRect();

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
