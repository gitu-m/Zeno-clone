#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QBrush>
#include <iostream>
#include <chrono>
#include <QDebug>
#include <QtConcurrent>
#include <typeinfo>

#include "Tile.h"
#include "Tesseract.h"
#include "Clone.h"
#include "Board.h"
#include "Player.h"

/*
*   0   - No Tile
*   1   - Regular Tile
*   2   - Tesseract
*   255 - Start Tile
*   999 - End Tile
*/

int level[][5] =  { {1  ,0  ,0  ,0  ,0  },
                    {99 ,1  ,0  ,0  ,999},
                    {0  ,1  ,0  ,0  ,1  },
                    {2  ,310,0  ,0  ,1  },
                    {1  ,502,0  ,0  ,1  }};

/*void Board::make_clone(QGraphicsScene * scene, const std::vector<Event> player_events){

    qDebug() << "Clone created";

    for (int i = 0; i < l; ++i)
    {
        for (int j = 0; j < b; ++j)
        {
            board[j][i] = level[j][i];
            // qDebug() << i << " "<< j << level[i][j] ;
            if (board[j][i])
            {
                delete tilePointers[j][i];
            }
            if (board[j][i] != 0) { // Render the tile
                // Tile * tile =
                tilePointers[j][i] = new Tile(board[j][i],j,i);;
                tilePointers[j][i]->setRect((11-l)*20 + i*40,(11-b)*20 + j*40,40,40);
                scene->addItem(tilePointers[j][i]); // Add tile to scene

                board[j][i] = 1;
            }
        }
    }
    past_self = new Clone(player_events, scene);
    // QtConcurrent::run(past_self->start_moving(player_events,scene));
    // connect(player,SIGNAL(level_over()),this,SLOT(remove_clone()));
}
*/
void Board::make_clone(QGraphicsScene * scene, const std::vector<Event> player_events){

    qDebug() << "Clone created";

    // for (int i = 0; i < l; ++i)
    // {
    //     for (int j = 0; j < b; ++j)
    //     {
    //         board[j][i] = level[j][i];
    //         // qDebug() << i << " "<< j << level[i][j] ;
    //         if (board[j][i])
    //         {
    //             delete tilePointers[j][i];
    //         }
    //         if (board[j][i] != 0) { // Render the tile
    //             // Tile * tile =
    //             tilePointers[j][i] = new Tile(board[j][i],j,i);;
    //             tilePointers[j][i]->setRect((11-l)*20 + i*40,(11-b)*20 + j*40,40,40);
    //             scene->addItem(tilePointers[j][i]); // Add tile to scene

    //             board[j][i] = 1;
    //         }
    //     }
    // }
    //Create Clone
    past_self = new Clone(player_events, scene);

    //Connection to make clone start running
    connect(this,SIGNAL(startClone()),past_self, SLOT(start_moving()));

    //Connection to set clone position
    connect(past_self, &Clone::makeMov , this, &Board::changeClonePos);

    past_self->moveToThread(&cloneThread);

    emit startClone();

    cloneThread.start();

}

void Board::changeClonePos(int X, int Y){ // Slot

    past_self->setPos(X, Y);

    QList<QGraphicsItem *> colliding_items = scene->collidingItems(past_self);

    for (int i = 0, n = colliding_items.size(); i < n ; i++){
        qDebug()<<n;
        if (typeid(*colliding_items[i]) == typeid(Tile)){
            int checkVal = qgraphicsitem_cast<Tile *> (colliding_items[i]) -> state;
            qDebug() <<checkVal;
            if (checkVal > 200 && checkVal < 400){
                // emit moveTile()
                    qDebug() <<checkVal*1;
                if (checkVal%10 != 0)
                {
                    qDebug() << X/40+checkVal%10<< " " << Y/40;
                    emit tilePointers[Y/40][X/40+checkVal%10]->makeMovsignal();
                }
                else
                {

                    // qDebug()  << X/40 << " " << Y/40+(checkVal/10)%10 ;
                    qDebug()  << X/40 << " " << Y/40+(checkVal/10)%10 <<tilePointers[Y/40+(checkVal/10)%10][X/40]->state;

                    emit tilePointers[Y/40+(checkVal/10)%10][X/40]->makeMovsignal();
                }
            }
        }
    }
}
Board::Board(QGraphicsScene * scene){
    int srtX,srtY;
    l = 5; // Set board size
    b = 5;
    // int **board;
    this->scene = scene;
    int initposX = (11-l)*20;
    int initposY = (11-b)*20;


    //Set tile positions


    board = new int*[l]; //Dynamically allocate board
    tilePointers = new Tile**[l];

    for (int i = 0 ; i < l ; i++){
        board[i] = new int[b]; // Allocate row
        tilePointers[i] = new Tile*[b];
    }

    for (int i = 0 ; i < l ; i++){
        for ( int j = 0 ; j < b ; j++){
            board[i][j] = level[i][j]; //Copy level into board
//            std::cout << board[i][j]<< " ";
        }
    }


    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < b; ++j) {
            // tilePointers[j][i] = NULL;
            if (board[j][i] != 0) { // Render the tile
                // Tile * tile =
                tilePointers[j][i] = new Tile(board[j][i],j,i);;
                tilePointers[j][i]->setRect(initposX + i*40,initposY + j*40,40,40);
                scene->addItem(tilePointers[j][i]); // Add tile to scene

                if (board[j][i] == 99){

                    srtX = i;
                    srtY = j;
                }

                else if (board[j][i] == 2){

                    Tesseract * tess = new Tesseract();
                    tess->setPos(initposX + i*40 + 12 ,initposY + 12 + j*40);
                    scene->addItem(tess);
                }

                board[j][i] = 1;
            }
        }
    }

    player = new Player();

    player->time_spawned = std::chrono::steady_clock::now();

    player->setRect(initposX + 12, initposY + 12,16,16);
    player->posX = srtX;
    player->posY = srtY;
    player->setPos(player->posX*40, player->posY*40);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    connect(player, SIGNAL(clone(QGraphicsScene *, std::vector <Event>)), this, SLOT(make_clone(QGraphicsScene *, const std::vector <Event>)));

}
