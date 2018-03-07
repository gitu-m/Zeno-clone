#include <QtConcurrent>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QInputDialog>
#include <QSound>

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

    setFixedSize(size());

    mBackground = new QSound("./resources/Sounds/AmbientMusic1.wav");

    mBackground->setLoops(QSound::Infinite);
//    mBackground->play();
    QFuture<void> f1 = QtConcurrent::run(mBackground, &QSound::play);


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

void Game::drawPanel(){
    // draws a panel at the specified location with the specified properties
    panel = new QGraphicsRectItem(440,0,200,480);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    panel->setBrush(brush);
    panel->setOpacity(1);
    scene->addItem(panel);

    QGraphicsTextItem * time = new QGraphicsTextItem(QString("Time Elapsed"));
    time->setDefaultTextColor(Qt::white);
    time->setFont(QFont("times",20));
    time->setPos(460,80);
    scene->addItem(time);

    Button * restartButton = new Button(QString("Restart Level"));

//    restartButton->boundingRect().setRect(panel->x(), panel->y(), restartButton->boundingRect().width(), restartButton->boundingRect().height());

    //Setting the co-ordinates for the restart button in the current scene
    int nxPos = scene->width() - panel->boundingRect().width()/2 - restartButton->boundingRect().width()/2;
    int nyPos = panel->boundingRect().height()/2 + restartButton->boundingRect().height()/2; ;
    restartButton->setPos(nxPos,nyPos);
    scene->addItem(restartButton);

    connect(restartButton, SIGNAL(clicked()), this, SLOT(restart()));

    Button * muteButton = new Button(QString("Mute/Unmute Sound"));

//    restartButton->boundingRect().setRect(panel->x(), panel->y(), restartButton->boundingRect().width(), restartButton->boundingRect().height());

    //Setting the co-ordinates for the restart button in the current scene
    int bxPos = scene->width() - panel->boundingRect().width()/2 - restartButton->boundingRect().width()/2;
    int byPos = restartButton->y() + restartButton->boundingRect().height() + 20;
    muteButton->setPos(bxPos,byPos);
    scene->addItem(muteButton);

    connect(muteButton, SIGNAL(clicked()), this, SLOT(mute()));

    leveldisplay = new QGraphicsTextItem(QString("Level: ") + QString::number(Level));
    leveldisplay->setDefaultTextColor(Qt::white);
    leveldisplay->setFont(QFont("times",20));
    leveldisplay->setPos(460,20);
//    leveldisplay->setParent(panel);
    scene->addItem(leveldisplay);

    userNamedisplay = new QGraphicsTextItem(userName);
    userNamedisplay->setDefaultTextColor(Qt::white);
    userNamedisplay->setFont(QFont("times",20));
    userNamedisplay->setPos(460,420);
//    userNamedisplay->setParent(panel);
    scene->addItem(userNamedisplay);

}

void Game::getUserName(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("Enter UserName"),tr("User name:"), QLineEdit::Normal,QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        userName = text;
}


void Game::Start(){

    qDebug() << "start";

    if (!Level){
        getUserName();
    }

    foreach(QGraphicsItem *item, scene->items()){

        scene->removeItem(item);
    }
    scene->clear();

    if (Level){ 
        delete brd;
        delete panel;
        delete leveldisplay;
    }

    // Increase Level for Next Call
    Level++;

    if (Level == 5){
        this->Close();
        return;
    }

    QGraphicsPixmapItem *foobar = new QGraphicsPixmapItem();

    switch(Level){
        qDebug() << "start";
        case 1:
        case 4:
            foobar->setPixmap(QPixmap("./resources/Backgrounds/level1.png")); break;
        case 2:
        case 3:
            foobar->setPixmap(QPixmap("./resources/Backgrounds/level2.png")); break;
//        case 3: foobar->setPixmap(QPixmap("./resources/Backgrounds/level3.png")); break;
    }

    scene->addItem(foobar);
    drawPanel();

    //Setup Board for the current level
    brd = new Board(scene,Level-1);

    //Connecting the level over signal emitted by the player to the start slot to render the new level
    connect(brd->player, SIGNAL(level_over()),this,SLOT(Start()));

    //Connecting the game over signal emitted by the player to the game over slot of the game
    connect(brd->player, SIGNAL(gameOverSignal()), this, SLOT(gameOver()));
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

void Game::gameOver(){

    foreach(QGraphicsItem *item, scene->items()){

        scene->removeItem(item);
    }

    scene->clear();

    if (Level){
        delete brd;
        delete panel;
        delete leveldisplay;
    }

    //Reset level
    Level = 0;


    //Setting the background for the game over screen
    QGraphicsPixmapItem *foo = new QGraphicsPixmapItem();
    foo->setPixmap(QPixmap("./resources/Backgrounds/blackGame.png"));
    scene->addItem(foo);


    //Setting the game over image
    QGraphicsPixmapItem *gameText = new QGraphicsPixmapItem();
    gameText->setPixmap(QPixmap("./resources/Backgrounds/gameoverwriting.png"));
    gameText->setPos(this->width()/2 - gameText->boundingRect().width()/2, 75);


    //Add image to screen
    scene->addItem(gameText);

    //Setting the text in the next button
    Button* menu = new Button(QString("Menu"));


    //Setting the co-ordinates for the menu button in the current scene
    int nxPos = this->width()/2 - menu->boundingRect().width()/2;
    int nyPos = 250;
    menu->setPos(nxPos,nyPos);
    scene->addItem(menu);

    connect(menu, SIGNAL(clicked()), this, SLOT(displayMenuSlot()));

}

void Game::restart(){

    foreach(QGraphicsItem *item, scene->items()){

        scene->removeItem(item);
    }
    scene->clear();

    if (Level){
        delete brd;
        delete panel;
        delete leveldisplay;
    }

    QGraphicsPixmapItem *foobar = new QGraphicsPixmapItem();

    switch(Level){
        qDebug() << "start";
        case 1:
        case 4:
            foobar->setPixmap(QPixmap("./resources/Backgrounds/level1.png")); break;
        case 2:
        case 3:
            foobar->setPixmap(QPixmap("./resources/Backgrounds/level2.png")); break;
//        case 3: foobar->setPixmap(QPixmap("./resources/Backgrounds/level3.png")); break;
    }

    scene->addItem(foobar);
    drawPanel();

    //Setup Board for the current level
    brd = new Board(scene,Level-1);

    //Connecting the level over signal emitted by the player to the start slot to render the new level
    connect(brd->player, SIGNAL(level_over()),this,SLOT(Start()));

    //Connecting the game over signal emitted by the player to the game over slot of the game
    connect(brd->player, SIGNAL(gameOverSignal()), this, SLOT(gameOver()));


}

void Game::mute(){

    if(!mBackground->isFinished()){
        mBackground->stop();
    }

    else mBackground->play();

    brd->player->setFocus();

}
void Game::Close(){
    //Clearing the scene before quitting
    scene->clear();

    //Setting the background for the exit screen
    QGraphicsPixmapItem *foo = new QGraphicsPixmapItem();
    foo->setPixmap(QPixmap("./resources/Backgrounds/blackGame.png"));
    scene->addItem(foo);

    //Setting the final string for the game
    QGraphicsTextItem * thanks = new QGraphicsTextItem(QString("Thanks for playing!"));
    thanks->setDefaultTextColor(Qt::white);
    thanks->setFont(QFont("Times", 40));
    thanks->setPos(scene->width()/2 - thanks->boundingRect().width()/2,100);
    scene->addItem(thanks);

    //Our names :)
    QGraphicsTextItem * gitu = new QGraphicsTextItem(QString("gitu-m : Gitanjali Mannepalli"));
    gitu->setDefaultTextColor(Qt::white);
    gitu->setFont(QFont("Times", 20));
    gitu->setPos(scene->width()/2 - gitu->boundingRect().width()/2,250);
    scene->addItem(gitu);

    QGraphicsTextItem * bhanu = new QGraphicsTextItem(QString("BhanuTabeti : Bhanu Prakash Goud Tabeti"));
    bhanu->setDefaultTextColor(Qt::white);
    bhanu->setFont(QFont("Times", 20));
    bhanu->setPos(scene->width()/2 - bhanu->boundingRect().width()/2,290);
    scene->addItem(bhanu);

    QGraphicsTextItem * sreekar = new QGraphicsTextItem(QString("sKAR04 : Sankalp Sreekar"));
    sreekar->setDefaultTextColor(Qt::white);
    sreekar->setFont(QFont("Times", 20));
    sreekar->setPos(scene->width()/2 - sreekar->boundingRect().width()/2,330);
    scene->addItem(sreekar);


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
