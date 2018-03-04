#include <QApplication>

#include "Game.h"

Game *game;

int main(int argc, char *argv[]){

    QApplication *newGame = new QApplication(argc, argv);

    game = new Game();
    game->show();

    int ret = newGame->exec();

    delete game;
    delete newGame;

    return ret;
}
