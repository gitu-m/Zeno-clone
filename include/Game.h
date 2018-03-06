#ifndef GAME_H

#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QWidget>
#include <QSound>

#include "Player.h"
#include "Board.h"
#include "Button.h"

class Game : public QGraphicsView{
	Q_OBJECT

	/*!
	* This thread runs simultaneously for the music.
	*/
    QThread mthread;

public:
	/*!
	* This variable stores the current level.
	*/
	int Level;

	/*!
	* The scene in which the board is to be displayed.
	*/
	QGraphicsScene *scene;
	/*!
    * The board associated with the game.
	*/
	Board *brd;

    QSound * mBackground;

	//To-Do
	QGraphicsRectItem* panel;
	//To-Do
	QGraphicsTextItem* leveldisplay;
	//To-Do
	QGraphicsTextItem* userNamedisplay;
	//To-Do
	QString userName = "User";


	/*!
	* Constructor for the game class.
	*/
    Game();

	/*!
	* This method is used to display text onto the screen.
	* Parameters:
	* QString : The text to be displayed.
	* First int : The size of the text.
	* Second int : The Y co-ordinate of the text.
	*/
	void showText(QString,int,int);
	/*!
	* This method displays the menu onto the screen.
	*/
	void displayMenu();

	//To-Do
    void drawPanel();

	//To-Do
	void getUserName();
	

public slots:
	/*!
	* This slot is responsible for starting the game.
	*/
	void Start();
	/*!
	* This slot is responsible for displaying the rules of the game.
	*/
	void Rules();
	/*!
	* This slot is responsible for displaying the closing the game.
	*/
	void Close();
	/*!
	* This slot is to ensure that menu is displayed after clicking the next button in the last rule.
	*/
	void displayMenuSlot();
    /*!
    * This slot is to display the game over screen when the player looses
    */
    void gameOver();
    /*!
    * This slot is responsible for restarting the level.
    */
    void restart();
    /*!
    * This slot is responsible to toggle the sound.
    */
    void mute();

};

#endif
