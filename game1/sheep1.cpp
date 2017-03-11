#include "sheep1.h"

Sheep1::Sheep1(int number, QObject *parent) :
    QObject(parent)
{
    setPixmap(QPixmap(number+".png"));
}
