#include "sheep1.h"
#include "helper.h"

Sheep1::Sheep1(int number, QObject *parent) :
    QObject(parent)
{
    m_angle = 0;

    setPixmap(QPixmap("pictures/sheep/"+QString::number(number)+".png"));
    setScale(0.13);
    setPos(500,0);
}

int Sheep1::getAngle() {
    return m_angle;
}

void Sheep1::setAngle(int angle){
    m_angle = angle;
}
