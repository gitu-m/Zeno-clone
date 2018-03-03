#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDebug>

#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Button.h"

Game::Game(){
	//Creating a scene to render the game
    scene = new QGraphicsScene();

    //Setting the dimensions of the current scene
    scene->setSceneRect(0,0,640,480);

    //Setting the main scene to be displayed to the current scene
    setScene(scene);

    //Create playlist
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/AmbientMusic1.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    //Play background music
    QMediaPlayer * bg_music = new QMediaPlayer();
    bg_music->setPlaylist(playlist);
    bg_music->play();

    playlist->moveToThread(&mthread);

    //Setting the current level to 0
	Level = 0;

    //Displaying the menu
    displayMenu();
}

void Game::Start(){

	scene->clear();

    qDebug() << "start";

    if (Level != 0) delete brd;

    //Setup Board for the current level
    brd = new Board(scene);

    // Increase Level for Next Call
    Level++;

    //Connecting the level over signal emitted by the player to the start slot to render the new level
    connect(brd->player, SIGNAL(level_over()),this,SLOT(Start()));
}

void Game::displayMenu(){
    //Setting the title string for the game
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Zeno"));
    QFont titleFont("Times",50);
    titleText->setFont(titleFont);

    //Setting the co-ordinates for the title string in the current scene
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    //Setting the text in the start button
    Button* playButton = new Button(QString("Play"));

    //Setting the co-ordinates for the play button in the current scene
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    scene->addItem(playButton);

    //Connecting the signal clicked to start the first level upon clicking
    connect(playButton,SIGNAL(clicked()),this,SLOT(Start()));

    //Setting the text in the quit button
    Button* quitButton = new Button(QString("Quit"));

    //Setting the co-ordinates for the quit button in the current scene
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    scene->addItem(quitButton);

    //Connecting the signal clicked to quit the game upon clicking
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
}
