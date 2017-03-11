#include "sheep1.h"

Sheep1::Sheep1(int number, QObject *parent) :
    QObject(parent)
{
    setPixmap(QPixmap("pictures/sheep/"+QString::number(number)+".png"));
    setScale(0.13);
    setPos(500,0);
}
