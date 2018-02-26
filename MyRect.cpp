#include "MyRect.h"
#include <QKeyEvent>
#include <iostream>
#include "Board.h"
#include "Game.h"

extern Game * game;

// Board *brd = game->brd;

// int **board = &boardpointer;
void MyRect::keyPressEvent(QKeyEvent *event){
//    std::cout << posX <<" " << posY << " ";
    if (event->key() == Qt::Key_Left){ // Move left
//        std::cout<<"left"<<std::endl;

        if (posX-1 >= 0 && game->brd->board[posY][posX-1] == 1){
            posX--;
        }
    }

    else if (event->key() == Qt::Key_Right){ // Move right
//        std::cout<<"right"<<std::endl;

        if (posX+1 < game->brd->l && game->brd->board[posY][posX+1] == 1){
            posX++;
        }
    }

    else if (event->key() == Qt::Key_Up){ //Move up
//        std::cout<<"up"<<std::endl;

        if (posY-1 >= 0 && game->brd->board[posY-1][posX] == 1){
            posY--;
        }
    }

    else if (event->key() == Qt::Key_Down){ // Movw down
//        std::cout<<"down"<<std::endl;

        if (posY+1 < game->brd->b && game->brd->board[posY+1][posX] == 1){
            posY++;
        }
    }

    setPos(posX*40, posY*40);
}
