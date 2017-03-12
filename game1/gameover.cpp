#include "gameover.h"

GameOver::GameOver(QObject *parent) :
    QObject(parent)
{
    this->setPixmap(QPixmap("pictures/gameover.png"));
    //setScale(0.3);
    setPos(0,170);
}
