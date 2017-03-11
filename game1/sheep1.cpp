#include "sheep1.h"

Sheep1::Sheep1(int number, QWidget *parent) :
    QObject(parent)
{
    setPixmap(QPixmap(number+".png"));
    this->scaled
}
