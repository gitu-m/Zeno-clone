#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "button.h"
#include <iostream>

Game::Game(){
	// create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,640,480); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
	
	Level = 0;   
    DisplayMenu();
}

void Game::Start(){
	scene->clear();

    // Setup Board for the current level
    brd = new Board(scene);

    // Increase Level for Next Call
    Level++;
    
}

void Game::DisplayMenu(){

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Zeno"));
    QFont titleFont("Times",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(Start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);

}

