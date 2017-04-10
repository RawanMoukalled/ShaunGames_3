#include "box.h"

/**
* \file box.cpp
* \brief Contains Box class definition
*/

/**
* Sets Box properties.
*/
Box::Box(QObject *parent) :
    QObject(parent), m_above(false), m_left(false), m_under(false), m_right(false), m_closedByUser(false), m_closedByPC(false)
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
    m_closedByPC = true;
}

/**
* Draws Bitzer on the box.
*/
void Box::drawBitzer() {
    setPixmap(QPixmap("pictures/Bitzer.png"));
    setScale(0.09);
    m_closedByUser = true;
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
bool Box::isClosed() const {
    return m_above && m_left && m_under && m_right;
}

/**
* Checks if the box is one line away from being closed.
*/
int Box::numberOfLinesDrawn() const {
    return static_cast<int>(m_above) + static_cast<int>(m_left) + static_cast<int>(m_under) + static_cast<int>(m_right);
}

/**
* \brief Returns whether the user has closed this box
* \returns Whether the user has closed this box
*/
bool Box::wasClosedByUser() const {
    return m_closedByUser;
}
