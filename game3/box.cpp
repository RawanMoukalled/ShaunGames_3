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
    setScale(0.1);
}

/**
* Draws Bitzer on the box.
*/
void Box::drawBitzer() {
    setPixmap(QPixmap("pictures/Bitzer.png"));
    setScale(0.09);
}

/**
* Marks that the top of the box has been drawn.
*/
void Box::setAbove() {
    m_above = true;
}

/**
* Marks that the left of the box has been drawn.
*/
void Box::setLeft() {
    m_left = true;
}

/**
* Marks that the bottom of the box has been drawn.
*/
void Box::setUnder() {
    m_under = true;
}

/**
* Marks that the right of the box has been drawn.
*/
void Box::setRight() {
    m_right = true;
}

/**
* Checks if the box has been closed.
*/
bool Box::isClosed() {
    return m_above && m_left && m_under && m_right;
}

/**
* Checks if the box is one line away from being closed.
*/
bool Box::threeSidesDrawn() {
    return static_cast<int>(m_above) + static_cast<int>(m_left) + static_cast<int>(m_under) + static_cast<int>(m_right);
}
