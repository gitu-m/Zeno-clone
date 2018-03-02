#include <QApplication>

#include "Game.h"

Game *game;

int main(int argc, char *argv[]){

    QApplication *newGame = new QApplication(argc, argv);

    game = new Game();
    game->show();

    return newGame->exec();
}
