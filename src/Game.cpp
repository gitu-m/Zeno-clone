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

void Game::Start(){

    qDebug() << "start";
	scene->clear();

    if (Level) delete brd;

    Level++;

    if (Level == 4){

        this->Close();

    }

    QGraphicsPixmapItem *foobar = new QGraphicsPixmapItem();

    switch(Level){
        qDebug() << "start";
        case 1: foobar->setPixmap(QPixmap("./resources/Backgrounds/level1.png")); break;
        case 2: foobar->setPixmap(QPixmap("./resources/Backgrounds/level2.png")); break;
        case 3: foobar->setPixmap(QPixmap("./resources/Backgrounds/level3.png")); break;
    }

    scene->addItem(foobar);

    //Setup Board for the current level
    brd = new Board(scene,Level-1);

    // Increase Level for Next Call
//    Level++;

    //Connecting the level over signal emitted by the player to the start slot to render the new level
    connect(brd->player, SIGNAL(level_over()),this,SLOT(Start()));
}

int ruleNum = 0;

void Game::Rules(){
    //Clearing the scene before showing rules
    scene->clear();

    //Setting the background for the rules screen
    QGraphicsPixmapItem *foo = new QGraphicsPixmapItem();
    foo->setPixmap(QPixmap("./resources/Backgrounds/rules.png"));
    scene->addItem(foo);

    //Setting the text in the next button
    Button* nextButton = new Button(QString("Next"));

    //Setting the co-ordinates for the play button in the current scene
    int nxPos = this->width()/2 - nextButton->boundingRect().width()/2;
    int nyPos = 300;
    nextButton->setPos(nxPos,nyPos);
    scene->addItem(nextButton);

    switch(ruleNum){
        case 0:{
            showText(QString("Rule 1:"),40,100);
            showText(QString("The square outline represents the player."),20,150);

            //Connecting the signal clicked to next rule upon clicking
            connect(nextButton,SIGNAL(clicked()),this,SLOT(Rules()));

            ++ruleNum;

            break;
        }
        case 1:{
            showText(QString("Rule 2:"),40,100);
            showText(QString("The bold square represents a tesseract."),20,150);

            //Connecting the signal clicked to next rule upon clicking
            connect(nextButton,SIGNAL(clicked()),this,SLOT(Rules()));

            ++ruleNum;

            break;
        }
        case 2:{
            showText(QString("Rule 3:"),40,100);
            showText(QString("Stepping on a tessseract spawns a new clone of yourself."),20,150);
            showText(QString("It also resets the board."),20,180);

            //Connecting the signal clicked to next rule upon clicking
            connect(nextButton,SIGNAL(clicked()),this,SLOT(Rules()));

            ++ruleNum;

            break;
        }
        case 3:{
            showText(QString("Rule 4:"),40,100);
            showText(QString("Clone follows the actions that you did before spawning it."),20,150);

            //Connecting the signal clicked to next rule upon clicking
            connect(nextButton,SIGNAL(clicked()),this,SLOT(Rules()));

            ++ruleNum;

            break;
        }
        case 4:{
            showText(QString("Rule 5:"),40,100);
            showText(QString("A moving tile can move by stepping on it's trigger"),20,150);
            showText(QString("A moving tile can be triggered only once."),20,180);

            //Connecting the signal clicked to next rule upon clicking
            connect(nextButton,SIGNAL(clicked()),this,SLOT(Rules()));

            ++ruleNum;

            break;
        }
        case 5:{
            showText(QString("Rule 6:"),40,100);
            showText(QString("A fading tile activates only by stepping on it's trigger."),20,150);

            //Connecting the signal clicked to show menu upon clicking
            connect(nextButton,SIGNAL(clicked()),this,SLOT(displayMenuSlot()));

            ruleNum = 0;

            break;
        }
    }
}

void Game::Close(){
    //Clearing the scene before quitting
    scene->clear();

    //Setting the background for the exit screen
    QGraphicsPixmapItem *foo = new QGraphicsPixmapItem();
    foo->setPixmap(QPixmap("./resources/Backgrounds/exit.png"));
    scene->addItem(foo);

    //Setting the final string for the game
    showText(QString("Thanks for playing!!"),40,100);

    //Our names :)
    showText(QString("Creators : "),25,200);
    showText(QString("gitu-m : Gitanjali"),20,250);
    showText(QString("BhanuTabeti : Bhanu"),20,290);
    showText(QString("sKAR04 : Sreekar"),20,330);
}

void Game::displayMenuSlot(){
    displayMenu();
}

void Game::displayMenu(){
    //Clearing the scene before showing menu
    scene->clear();

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
    connect(rulesButton,SIGNAL(clicked()),this,SLOT(Rules()));

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
