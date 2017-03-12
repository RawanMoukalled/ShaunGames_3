#include "sheep1.h"
#include "helper.h"

/**
* Sets the properties of the sheep.
*/
Sheep1::Sheep1(int number, bool status, QObject *parent) :
    QObject(parent)
{
    m_angle = 0;

    setPixmap(QPixmap("pictures/sheep/"+QString::number(number)+".png"));
    setScale(0.10);
    setPos(500,0);

    m_inLine = status;
}

/**
* Frees allocated memory.
*/
Sheep1::~Sheep1() {
}

int Sheep1::getAngle() const {
    return m_angle;
}

void Sheep1::setAngle(int angle){
    m_angle = angle % 360;
}

void Sheep1::setInLine(bool status) {
    m_inLine = status;
}

bool Sheep1::isInLine() {
    return m_inLine;
}
