#include "box.h"

/**
* \file box.cpp
* \brief Contains Box class definition
*/

/**
* Sets Box properties.
*/
Box::Box(QObject *parent) :
    QObject(parent), m_above(false), m_left(false), m_under(false), m_right(false)
{
}

/**
* Frees allocated memory.
*/
Box::~Box() {

}

/**
* Draws Shaun on the box.
*/
void Box::drawShaun() {
    setPixmap(QPixmap("pictures/shaun.png"));
    setScale(0.12);
}

/**
* Draws Bitzer on the box.
*/
void Box::drawBitzer() {
    setPixmap(QPixmap("pictures/Bitzer.png"));
    setScale(0.05);
}
