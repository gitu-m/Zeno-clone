#include "Board.h"
#include "MyRect.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <iostream>

Board::Board(QGraphicsScene * scene){

    l = 5; // Set board size
    b = 5;
    // int **board;
    int initX = (11-l)*20;
    int initY = (11-b)*20;
    //Set tile positions
    int level[][5] =  {{1,0,0,0,0},
                        {1,1,0,0,1},
                        {0,1,0,0,1},
                        {0,1,1,1,1},
                        {1,1,0,0,1}};

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
            if (board[j][i] == 1) { // Render the tile
                QGraphicsRectItem * rect = new QGraphicsRectItem();
                rect->setRect(initX + i*40,initY + j*40,40,40);
                scene->addItem(rect); // Add tile to scene
            }
        }
    }

    player = new MyRect();

    // std::cout <<" Hi ";
    player->posX = 0;
    player->posY = 0;
    player->setRect(player->posX*40 + initX + 12,player->posY*40 + initY + 12,16,16);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);
}


