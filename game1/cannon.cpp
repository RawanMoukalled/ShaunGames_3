#include "cannon.h"
#include <QtGui>

/**
* \file cannon.cpp
* \brief Contains Cannon class definition
*/

/**
* Sets the cannon image and initializes variables.
*/
Cannon::Cannon(QObject *parent) :
    QObject(parent)
{
    setPixmap(QPixmap("pictures/cannon.png"));
    setScale(0.3);
    setPos(250,250);

}


/**
* This function checks the position of the mouse and rotates the cannon accordingly.
*/
void Cannon::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << QString::number(event->pos().x());
    qDebug() << QString::number(event->pos().y());
}
