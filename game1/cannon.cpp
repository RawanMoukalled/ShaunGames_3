#include "cannon.h"

/**
* \file cannon.cpp
* \brief Contains Cannon class definition
*/


/**
* Sets the cannonimage and initializes variables.
*/
Cannon::Cannon(QObject *parent) :
    QObject(parent)
{
    this->setPixmap(QPixmap("pictures/cannon.png"));
    setScale(0.3);
    setPos(250,250);
}

void Cannon::keyPressEvent(QKeyEvent *event) {
    setRotation(rotation()+5);
}
