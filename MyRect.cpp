#include "MyRect.h"
#include <QKeyEvent>
#include <iostream>
// #include "board.h"
extern int l, b, board[][5];

// int **board = &boardpointer;
void MyRect::keyPressEvent(QKeyEvent *event){
    std::cout<<board[posY][posX]<<" ";
    if (event->key() == Qt::Key_Left){
        std::cout<<"left"<<std::endl;
        if (posX-1 >= 0 && board[posY][posX-1] == 1){
            posX--;
        }
    }
    else if (event->key() == Qt::Key_Right){
        std::cout<<"right"<<std::endl;
        if (posX+1 < l && board[posY][posX+1] == 1){
            posX++;
        }
    }
    else if (event->key() == Qt::Key_Up){
        std::cout<<"up"<<std::endl;
        if (posY-1 >= 0 && board[posY-1][posX] == 1){
            posY--;
        }
    }
    else if (event->key() == Qt::Key_Down){
        std::cout<<"down"<<std::endl;
        if (posY+1 < b && board[posY+1][posX] == 1){
            posY++;
        }
    }
    setPos(posX*40, posY*40);
}
