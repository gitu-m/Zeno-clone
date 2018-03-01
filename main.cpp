#include <QApplication>
#include "Game.h"

Game * game;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    game = new Game;
    game->show();
    a.setQuitOnLastWindowClosed(true);
    return a.exec();
}
