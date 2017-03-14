#include "gameover.h"

GameOver::GameOver(bool win, QObject *parent) :
    QObject(parent)
{
    if(!win){
        this->setPixmap(QPixmap("pictures/gameover.png"));
    } else {
        this->setPixmap(QPixmap("pictures/gameoverwin.png"));
    }

    setPos(0,170);
    setZValue(2);
}
