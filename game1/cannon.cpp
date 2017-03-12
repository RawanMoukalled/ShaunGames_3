#include "cannon.h"
#include <QtGui>

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
    setPos(300,250);
}

void Cannon::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        int rot = rotation()-5;
        if (rot < 0) {
            rot = rot + 360;
        }
        setRotation(rot);
    }
    else if (event->key() == Qt::Key_Right) {
        int rot = rotation()+5;
        if (rot >= 360) {
            rot = rot - 360;
        }
        setRotation(rot);
    }
    else if (event->key() == Qt::Key_Space) {
        qDebug() << "Rotation: " << rotation();
    }
}
