#include "cannon.h"
#include "game1scene.h"

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
    setTransformOriginPoint(0,45);
    setPos(290,210);
    setZValue(0);
}

/**
* Frees allocated memory.
*/
Cannon::~Cannon() {
}

/**
* Checks the key that triggered the event.
* If the key was a left or right arrow key, the cannon rotates left or right.
* If the key was a space, a sheep is thrown.
*/
void Cannon::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        int rot = rotation()-5;
        if (rot < 0) {
            rot = rot + 360;
        }
        setRotation(rot);

        Game1Scene *s = static_cast<Game1Scene*>(scene());
        s->moveCurrentSheep(false);
    }
    else if (event->key() == Qt::Key_Right) {
        int rot = rotation()+5;
        if (rot >= 360) {
            rot = rot - 360;
        }
        setRotation(rot);

        Game1Scene *s = static_cast<Game1Scene*>(scene());
        s->moveCurrentSheep(true);
    }
    else if (event->key() == Qt::Key_Space) {
        Game1Scene *s = static_cast<Game1Scene*>(scene());
        s->fireSheep();
    }
}
