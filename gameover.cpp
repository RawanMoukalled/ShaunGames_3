#include "gameover.h"

/**
* \file gameover.cpp
* \brief Contains GameOver class definition
*/

/**
* Sets origin of the image depending on win state.
*/
GameOver::GameOver(bool win, QObject *parent) :
    QObject(parent)
{
    if(!win){
        this->setPixmap(QPixmap("pictures/gameover.png"));
    } else {
        this->setPixmap(QPixmap("pictures/gameoverwin.png"));
    }

    setPos(0,170);
    setZValue(5);
}

/**
* Frees allocated memory.
*/
GameOver::~GameOver() {
}
