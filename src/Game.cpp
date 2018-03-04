#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDebug>
#include <QGraphicsPixmapItem>

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

void Game::showText(QString foo,int size,int pos){
    QGraphicsTextItem* fooText = new QGraphicsTextItem(foo);
    QFont fooFont("Times",size);
    fooText->setFont(fooFont);

    //Setting the co-ordinates for the title string in the current scene
    int fxPos = this->width()/2 - fooText->boundingRect().width()/2;
    int fyPos = pos;
    fooText->setPos(fxPos,fyPos);
    scene->addItem(fooText);
}

void Game::Close(){
    //Clearing the scene before quitting
    scene->clear();

    //Setting the final string for the game
    showText(QString("Thanks for playing!!"),40,100);

    //Our names :)
    showText(QString("Creators : "),25,200);
    showText(QString("gitu-m : Gitanjali"),20,250);
    showText(QString("BhanuTabeti : Bhanu"),20,290);
    showText(QString("sKAR04 : Sreekar"),20,330);
}

void Game::displayMenu(){
    //Setting the background for menu
    QGraphicsPixmapItem *foobar = new QGraphicsPixmapItem();
    foobar->setPixmap(QPixmap("./resources/Backgrounds/menu.png"));
    scene->addItem(foobar);

    //Setting the title string for the game
    showText(QString("Zeno"),50,100);

    //Setting the text in the start button
    Button* playButton = new Button(QString("Play"));

    //Setting the co-ordinates for the play button in the current scene
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 200;
    playButton->setPos(bxPos,byPos);
    scene->addItem(playButton);

    //Connecting the signal clicked to start the first level upon clicking
    connect(playButton,SIGNAL(clicked()),this,SLOT(Start()));

    //Setting the text in the start button
    Button* rulesButton = new Button(QString("Rules"));

    //Setting the co-ordinates for the rules button in the current scene
    int rxPos = this->width()/2 - rulesButton->boundingRect().width()/2;
    int ryPos = 275;
    rulesButton->setPos(rxPos,ryPos);
    scene->addItem(rulesButton);

    //Connecting the signal clicked to start the first level upon clicking
    //connect(rulesButton,SIGNAL(clicked()),this,SLOT(Rules()));

    //Setting the text in the quit button
    Button* quitButton = new Button(QString("Quit"));

    //Setting the co-ordinates for the quit button in the current scene
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    scene->addItem(quitButton);

    //Connecting the signal clicked to quit the game upon clicking
    connect(quitButton,SIGNAL(clicked()),this,SLOT(Close()));
}
