#include "Player.h"
#include <QKeyEvent>
#include <iostream>
#include "Board.h"
#include "Game.h"
#include <chrono>
//#include <ctime>

extern Game * game;

void Player::keyPressEvent(QKeyEvent *event){

    key_event key_pressed;

    key_pressed.key = event;

    std::chrono::steady_clock::time_point time_event = std::chrono::steady_clock::now();
    key_pressed.key_time = time_event - time_spawned;

    event_queue.push_back(key_pressed); // Push this event to queue

   // std::cout << posX << " " << posY << "\n";

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
