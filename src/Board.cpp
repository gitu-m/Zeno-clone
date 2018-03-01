#include "Board.h"
#include "Player.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QBrush>
#include <iostream>
#include <chrono>
#include "Tile.h"
#include "Tesseract.h"
#include "Clone.h"

#include <QDebug>
#include <QtConcurrent>

/*
*   0   - No Tile
*   1   - Regular Tile
*   2   - Tesseract
*   255 - Start Tile
*   999 - End Tile
*/

void Board::make_clone(QGraphicsScene * scene, const std::vector<Event> player_events){

    qDebug() << "Clone created";

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

}

Board::Board(QGraphicsScene * scene){
    int srtX,srtY;
    l = 5; // Set board size
    b = 5;
    // int **board;
    int initposX = (11-l)*20;
    int initposY = (11-b)*20;
    

    //Set tile positions
    int level[][5] =  { {1  ,0  ,0  ,0  ,0  },
                        {255,1  ,0  ,0  ,999},
                        {0  ,1  ,0  ,0  ,2  },
                        {0  ,1  ,1  ,1  ,1  },
                        {1  ,1  ,0  ,0  ,1  }};

    board = new int*[l]; //Dynamically allocate board

    for (int i = 0 ; i < l ; i++){
        board[i] = new int[b]; // Allocate row
    }

    for (int i = 0 ; i < l ; i++){
        for ( int j = 0 ; j < b ; j++){
            board[i][j] = level[i][j]; //Copy level into board
//            std::cout << board[i][j]<< " ";
        }
    }


    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < b; ++j) {
            if (board[j][i] != 0) { // Render the tile
                Tile * tile = new Tile(board[j][i]);
                tile->setRect(initposX + i*40,initposY + j*40,40,40);
                scene->addItem(tile); // Add tile to scene

                if (board[j][i] == 999){

                    /* code */
                }
                else if (board[j][i] == 255){

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

